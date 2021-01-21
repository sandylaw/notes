#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#  SandyLaw <freelxs@gmail>  Mon, 30 Nov 2020 08:32:27 PM +0800

import os
import re

with os.popen('who', 'r') as f:
    for eachLine in f:
        print(re.split(r'\s\s+', eachLine.strip()))
