# -*- coding: utf-8 -*-
import re
import os
import sys
import html
import time
from textcodecpub import *

def readFileUtf8(filename):
    print ("filename:%s" % filename)
    try:
        f = open(filename, 'r',encoding='UTF-8')
        result =  f.readlines()
        print(result)
        return result
    except Exception as e:
        print("exception:%s" %e)
    finally:
        if f:
            f.close()
