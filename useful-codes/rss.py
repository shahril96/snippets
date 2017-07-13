#!/usr/bin/env python

import sys
import re
import textwrap

try:                import urllib.request as urllib_request # for python 3
except ImportError: import urllib2 as urllib_request # for python 2

try:                from html.parser import HTMLParser # for python 3
except ImportError: from HTMLParser import HTMLParser # for python 2

USER_AGENT    = 'Mozilla/5.0 (Windows NT 6.3; rv:36.0) Gecko/20100101 Firefox/36.0'
WRAP_STRING   = 50 # how much in one line before wrapping
MAX_TITLES    = 5  # how much titles to display
INITIAL_INDEX = 0  # starts with n-th index first

def main():

    global MAX_TITLES, USER_AGENT, WRAP_STRING, INITIAL_INDEX

    if len(sys.argv) <= 1:
        sys.exit('Not enought arguments')
    
    if len(sys.argv) == 3:
        MAX_TITLES = int(sys.argv[2])

    try:

        rss  = urllib_request.urlopen(urllib_request.Request( sys.argv[1], headers={'User-Agent': USER_AGENT} ))
        text = HTMLParser().unescape(rss.read().decode("utf-8"))
        list_titles = re.findall('<title>(.*?)<\/title>', text)[INITIAL_INDEX:MAX_TITLES+INITIAL_INDEX]        

        i = 1
        for each in list_titles:
            each = textwrap.fill(each, WRAP_STRING)
            each = "\n{}".format(' ' * (len(str(i)) + 2)).join(each.split("\n"))
            print("{}. {}".format(i, each))
            i += 1
    
    except Exception as e:
        print('Failed to fetch RSS data.\n\n{}'.format(textwrap.fill(str(e.reason), WRAP_STRING)))

if __name__ == '__main__':
    main()