
import os
import sys
import re
import subprocess
import time

PPPD_WAITTIMEOUT = 10

#####################################
## network & ppp specified functions
#####################################

def papsecret(username, password):

    papfile = """\r# Secrets for authentication using PAP
                 \r# client	server	secret			IP addresses
                 \r"{}" provider "{}"
                 \r""".format(username, password)

    with open('/etc/ppp/pap-secrets', 'w') as f:
        f.write(papfile)

def peerprovider(username, interface):

    providerfile = """\rplugin rp-pppoe.so      # use Roaring Penguin's PPPoE plugin
                      \r{}                      # network interface
                      \ruser "{}"               # login name
                      \rusepeerdns              # obtains DNS from provider
                      \rpersist
                      \rdefaultroute
                      \rhide-password
                      \rnoauth""".format(interface, username)
    
    with open('/etc/ppp/peers/provider', 'w') as f:
        f.write(providerfile)

def resolvconf(dns):
    with open('/etc/resolv.conf', 'w') as f:
        f.write('nameserver {}'.format(dns))


def ipaddr(filter=None):

    relist = {}
    relist['interf'] = re.compile('^\s(.*?): ')
    relist['inet']   = re.compile('inet\s(.*?)\s')
    relist['brd']    = re.compile('inet.*brd\s(.*?)\s')
    relist['inet6']  = re.compile('inet6\s(.*?\s)')
    relist['type']   = re.compile('link\/(.*?)\s')
    relist['hwaddr'] = re.compile('link\/.*?\s(.*?)\s')
    relist['attr']   = re.compile('<(.*?)>')

    parsed = []
    getipaddr = "\n{}".format(system('ip address show'))
    for each in re.split('\n\d+:', getipaddr):
        curritem = {}
        for type, regex in relist.items():
            result = regex.findall(each)
            if len(result) > 0:
                if type == 'attr': curritem[type] = result[0].split(',')
                else:              curritem[type] = result[0]
        if len(curritem) > 0:
            if filter == None:
                parsed.append(curritem)
            elif curritem['interf'] == filter:
                return curritem
    
    return parsed

###############################
## system specified functions
###############################

def system(str):
    return subprocess.Popen(str, shell=True, stdout=subprocess.PIPE).communicate()[0].decode("utf-8")

def validCommand(str):
    try:
        system(str)
        return True
    except:
        return False

def pppexist():
    ''' Check if there is current pppd running '''
    for each in ipaddr():
        if 'POINTOPOINT' in each['attr']:
            return True 
    return False

######

def main():

    if not os.geteuid() == 0:
        print('Script not started as root. Running sudo..')
        args = ['sudo', sys.executable] + sys.argv + [os.environ]
        os.execlpe('sudo', *args)

    if len(sys.argv) != 2:
        sys.exit('{} <ip>'.format(sys.argv[0]))

    if not validCommand('php --version'):
        sys.exit('Make sure PHP is installed')
    
    if pppexist():
        sys.exit('There is currently existing pppd instance running!')

    # get interface input from user
    while(True):
        interf = ipaddr()
        for i in range(len(interf)):
            print('[{}] {}'.format(i, interf[i]['interf']))
        chosen = int(input('Please choose the interface: '))
        if chosen >= 0 and chosen < len(interf):
            break
    
    # get username & password from router
    ip       = sys.argv[1]
    iprange  = sys.argv[1].split('.')[-1]
    print('\nContacting {} to get the streamyx data...'.format(ip), end='')
    output = system('php tmpunk.php -ip {} -range {}-{}'.format(ip, iprange, iprange))

    # only innacom-type router works
    if 'Innacom' not in output:
        sys.exit('\nNo valid router\'s HTTP server found or router isn\'t Innacom\n')

    # extract the appropriate data for our cause
    reExtract = 'User\s:\s(.*)?\n.*:\s(.*)?'
    data = re.findall(reExtract, output)[0]

    # ask router to restart
    print('\nSending signal to {} to restart itself...'.format(ip), end='')
    output = system('php tmpunk.php -reboot {} -timeout 5'.format(ip))
    if 'rebooting now' not in output:
        sys.exit('\nFailed to restart the router! Exiting...\n')

    # modifies the config
    papsecret(data[0], data[1])
    peerprovider(data[0], interf[chosen]['interf'])
    print('\nPatched pap-secrets and provider files.')

    # run the pppd
    print('Run pppd with default provider config.')
    print('Waiting for {} second(s) for pppd connection to up...'.format(PPPD_WAITTIMEOUT), end='')
    sys.stdout.flush()
    
    system('pon')
    
    # wait until the interface is up
    time.sleep(PPPD_WAITTIMEOUT)
    output = system('journalctl -b --since "{} seconds ago" | grep pppd'.format(PPPD_WAITTIMEOUT+10))
    if 'PAP authentication succeeded' not in output:
        sys.exit('\npppd connection failed!\n')
    
    # change current DNS to Google's DNS
    resolvconf('8.8.8.8')

    # get new interface data & set new route
    pppinterf = re.findall('Using interface (.*)', output)[0]
    interf = ipaddr(pppinterf)
    system('ip route add default via {} dev {}'.format(interf['inet'], interf['interf']))
    
    print('\nNew route \'{}\' has been set!'.format(interf['inet']))
    print('Have a nice day! :)\n')


if __name__ == '__main__':
    main()