#!/usr/bin/env python
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Sat, 28 Nov 2020 06:15:17 PM +0800
from random import random
from math import sqrt
from time import time

DARTS = 1200000000
HITS = 0
time()
for i in range(1,DARTS):
    x, y = random(), random()
    dist = sqrt(x**2 + y**2)
    if dist <= 1.0:
        HITS = HITS +1
PI = 4 * (HITS/DARTS)
print("Pi的值是 %s" %PI)
print("程序运行时间是 %-5.5ss" %time())
