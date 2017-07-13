
import os
import sys
import re
import subprocess
import pprint

def papsecret(username, password):

    papfile = """\r# Secrets for authentication using PAP
                 \r# client	server	secret			IP addresses
                 \r"{}" provider "{}"
                 \r""".format(username, password)

    with open('/etc/ppp/pap-secrets', 'w') as f:
        f.write(papfile)

def peerprovider(username, interface):

    providerfile = """\rplugin rp-pppoe.so      # use Linux's kernel-mode PPPoE
                      \r{}                      # network interface
                      \ruser "{}"               # login name
                      \rusepeerdns              # obtains DNS from provider
                      \rpersist
                      \rdefaultroute
                      \rhide-password
                      \rnoauth""".format(interface, username)
    
    with open('/etc/ppp/peers/provider', 'w') as f:
        f.write(providerfile)

def ipaddr():
    
    relist = {}
    relist['interf'] = re.compile('^\s(.*?): ')
    relist['inet']   = re.compile('inet\s(.*?\s)')
    relist['brd']    = re.compile('inet.*brd\s(.*?\s)')
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
            parsed.append(curritem)

    return parsed

def system(str):
    return subprocess.Popen(str, shell=True, stdout=subprocess.PIPE).communicate()[0].decode("utf-8")

def main():

    if not os.geteuid() == 0:
        sys.exit('Script must be run as root')

    if len(sys.argv) != 3:
        sys.exit('{} <username> <password>'.format(sys.argv[0]))

    while(True):
        interf = ipaddr()
        for i in range(len(interf)):
            print("[{}] {}".format(i, interf[i]['interf']))
        chosen = int(input("Please choose the interface: "))
        if chosen >= 0 and chosen < len(interf):
            break

    papsecret(sys.argv[1], sys.argv[2])
    peerprovider(sys.argv[1], interf[chosen]['interf'])

    print("\n -> Now run your PPP connection using `pon`, to off use `poff`")
    print("\n -> also change default route with `sudo ip route add default via <ip> dev ppp0`\n")


if __name__ == '__main__':
    main()