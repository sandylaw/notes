#!/usr/bin/env python
# -*- coding: UTF-8 -*-

MONTHS="JanFebMarAprMayJunJulAugSepOctNovDec"
n=input("请输入月份数（1-12）：")
pos=(int(n)-1) * 3
monthAbbrev=MONTHS[pos:pos+3]
print("月份简写是" +monthAbbrev+".")
