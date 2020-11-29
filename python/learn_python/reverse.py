#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Sun, 29 Nov 2020 10:57:14 AM +0800

def reverse(s):
    if s == "":
        return s
    else:
        return reverse(s[1:]) + s[0]
