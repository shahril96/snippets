
'''
Note:

Sometimes when you have too many cousin celebrating 
Eid Al-Fitr in your house, with the limited and slow internet, thing
can go rage fast.

Here is the script, to automatically block all wireless MAC by
sending all the MACs into the block list of D-Link DSL-2640B.

Do whatever you want then, but don't forget to release all the MACs 
back, you don't want to be a jerk, don't you right?

Usage:

This script needs `requests` : http://docs.python-requests.org/en/master/

When you're running this script, it will do two things:

    a) If there is none blocked mac, then it will fetch all wireless MAC addresses
       and insert these into the block list
    b) If there is blocked mac, then it will remove (release) all the MACs, giving back
       freedom to the users. :)

'''


import requests
import re
import random
import string

USERNAME = 'admin'
PASSWORD = 'admin'
ADDRESS  = '192.168.1.1'


def block_all():
    curr_sess = requests.Session()
    r = curr_sess.post('http://{}/index.html'.format(ADDRESS), data={'username': USERNAME, 'password': PASSWORD})
    list_mac = get_wireless_clients()
    for each in list_mac: # add each mac into the list
        rndstr = ''.join(random.sample(string.ascii_lowercase, 7))
        print("Blocking {} with name '{}'...".format(each, rndstr))
        curr_sess.get('http://{}/todmngr.tod?action=add&&username={}&mac={}&iptfltEntryId=-1'.format(ADDRESS, rndstr, each))
    if len(get_blocked_macs()) != len(list_mac):
        print("Error: Not all MAC addresses successfully added into the list!")


def release_all(macs):
    curr_sess = requests.Session()
    r = curr_sess.post('http://{}/index.html'.format(ADDRESS), data={'username': USERNAME, 'password': PASSWORD})
    curr_sess.get('http://{}/todmngr.tod?action=remove&rmLst={}&change=1'.format(ADDRESS, ''.join(['{}, '.format(e[0]) for e in macs])))
    if len(get_blocked_macs()) > 0:
        print("Removing MACs failed! The mac addresses might still be there....")


def get_wireless_clients():
    curr_sess = requests.Session()
    r = curr_sess.post('http://{}/index.html'.format(ADDRESS), data={'username': USERNAME, 'password': PASSWORD})
    r = curr_sess.get('http://{}/wlstationlist.cmd'.format(ADDRESS))
    return [e[0] for e in re.findall('(([0-9A-F]{2}:){5}[0-9A-F]{2})', r.text)]


def get_blocked_macs():
    curr_sess = requests.Session()
    r = curr_sess.post('http://{}/index.html'.format(ADDRESS), data={'username': USERNAME, 'password': PASSWORD})
    r = curr_sess.get('http://{}/todadd.html'.format(ADDRESS))
    list_mac = [(e[0], e[1]) for e in re.findall('lblUsername.*>(.*?)<\/label.*\n.*lblMac.*>(.*?)<\/label', r.text)]
    return list_mac


def main():
    
    blocked_macs = get_blocked_macs()

    if len(blocked_macs) > 0:

        print("\nList of blocked wireless MACs:")
        print('\n'.join([each for each in blocked_macs]))
        inp = input("\nAre you sure you want to proceed? [y/n] : ")

        if inp == 'y':
            print("Releasing all blocked wireless mac addresses")
            release_all(blocked_macs)
        else:
            print("Bad choice! :(")

    else:

        print("\nList of all wireless MACs:")
        print('\n'.join([each for each in get_wireless_clients()]))
        inp = input("\nAre you sure you want to proceed? [y/n] : ")

        if inp == 'y':
            print("Blocking all wireless mac addresses from this network")
            block_all()
        else:
            print("Good choice! Bye2 :)")


if __name__ == '__main__':
    main()