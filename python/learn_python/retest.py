#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Sat, 05 Dec 2020 03:16:52 PM +0800

"""This is a re test"""

import re
import requests
#f = open("re.txt")
#for line in f:
#    if line.startswith('MX') and line.endswith('MX\n'):
#        print(line)
#a = 'python'
#b = re.match('^p(.*?)n$',a).group()
#print(b)

#a = 'python38428192by2211'
## re.search only once
#b = re.search('\d+?',a).group()
#print(b)

#a = 'python38428192by2211'
#res = re.compile('\d+')
#b = re.findall(res,a)
#print(b)

#a = 'python38428192by2211'
#res = re.compile('\d+')
#b = re.sub(res,'+',a)
#print(b)

#a = 'python38428192by2211'
#res = re.compile('\d+')
#b = re.split(res,a)
#print(b)

url = 'https://mirrors.ustc.edu.cn/debian/pool/main/b/base-files/'
resp = requests.get(url)
res = re.compile(r'<a href="(.*?)">?')
reg = re.findall(res, resp.text)
print(reg)
