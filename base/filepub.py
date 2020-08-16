# -*- coding: utf-8 -*-
import re
import os
import sys
import html
import time
from textcodecpub import *

def readFileUtf8(filename):
    filename = filename.replace("/", os.sep)
    print ("filename:%s" % filename)
    try:
        f = open(filename, 'r',encoding='UTF-8')
        result =  f.readlines()
        print(result)
        return result
    except Exception as e:
        print("exception:%s" %e)
        return e
    finally:
        if f:
            f.close()

def readFileGBK(filename):
    filename = filename.replace("/", os.sep)
    print ("filename:%s" % filename)
    try:
        f = open(filename, 'r',encoding='GBK')
        result =  f.readlines()
        print(result)
        return result
    except Exception as e:
        print("exception:%s" %e)
        return e
    finally:
        if f:
            f.close()



def openfileordirpath(path):
    os.system("start explorer " + path)


def getcwd():
    return os.getcwd()

def getcwdwithpath(str):
    return getcwd() + os.sep + str;

def opencurrentcwd():
    openfileordirpath(getcwd())