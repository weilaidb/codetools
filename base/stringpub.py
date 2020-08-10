# -*- coding: utf-8 -*-


def splitbynewline(str):
    try:
        return str.split('\n')
    except Exception as e:
        print("exception:%s" %e)
        return e

def showlist(list):
    for i in range(len(list)):
        print(list[i])
