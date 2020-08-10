# -*- coding: utf-8 -*-
import re
import os
import sys
import html
import time

def readFile(filename):
    print ("filename:%s" % filename)
    try:
        f = open(filename, 'r')
        print(f.read())
        # return f.read()
    finally:
        if f:
            f.close()
def test():
    print("test")