#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Sun, 29 Nov 2020 10:38:38 AM +0800

def createTable(principal, apr):
    for year in range(1,11):
        principal = principal * (1 + apr)
        print("%2d"%year, end = '')
        total = caculateNum(principal)
        print("*" * total)
    print("0.0 K    2.5K    5.0K    7.5K    10.0k")

def caculateNum(principal):
    total = int(principal*4/1000.0)
    return total

def main():
    print("This program plots the growth of a 10-year investment.")
    principal = eval(input("Enter the initial principal:"))
    apr = eval(input("Enter the annualized interest rate:"))
    createTable(principal,apr)

main()
