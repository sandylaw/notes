#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Sun, 29 Nov 2020 10:48:37 AM +0800

def fact(n):
    if n == 0:
        return 1
    else:
        return n * fact(n-1)
def main():
    x = fact(5)
    print("5! is %d" % x)

main()
