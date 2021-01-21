#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Sun, 29 Nov 2020 06:05:48 PM +0800

def main():
    fname = input("Enter filename:")
    infile = open(fname, 'r')
    data = infile.read()
    print(data)

main()
