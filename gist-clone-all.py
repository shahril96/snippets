#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Clone all gists of GitHub username given on the command line."""

import subprocess
import sys
import requests

if len(sys.argv) > 1:
    gh_user = sys.argv[1]
else:
    print("Usage: gist-clone-all.py <GitHub username>")
    sys.exit(1)

i = 1
while True:

    data = requests.get('https://api.github.com/users/{}/gists?page={}'.format(gh_user, i)).json()

    # break if API returns no data
    if not data:
        break

    for gist in data:
        ret = subprocess.call(['git', 'clone', gist['git_pull_url']])
        if ret != 0:
            print("ERROR cloning gist %s. Please check output." % gist['id'])

    i += 1