#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Mon, 30 Nov 2020 09:19:48 PM +0800

from random import randrange, choice
from string import ascii_lowercase as lc
from sys import maxsize
from time import ctime

tlds = ('com', 'edu', 'net', 'org', 'gov')
for i in range(randrange(5,11)):
    dtint = randrange(maxsize)
    print(dtint)
    dtstr = ctime(dtint//9999999)
    llen = randrange(4, 8)
    login = ''.join(choice(lc) for j in range(llen))
    dlen = randrange(llen, 13)
    dom = ''.join(choice(lc) for j in range(dlen))
    print('%s::%s@%s.%s::%d-%d-%d' %(dtstr, login, dom, choice(tlds), dtint,
            llen, dlen))

