#!/usr/bin/python3

import os
import shutil


for r,d,files in os.walk("./"):
    for f in files:
        if f[0] != "_" and f[-4:] == ".txt":
            shutil.copyfile(r+"/"+f, r+"/_"+f)
        