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

def listshow(list):
    showlist(list)


def listuniquesort(inlist):
    inlist = list(set(inlist))
    inlist.sort()
    return inlist

def listunique(inlist):
    inlist = list(set(inlist))
    return inlist

def listsort(inlist):
    inlist.sort()
    return inlist


def stringstrip(str):
    return str.strip()

def stringstriplen(str):
    return len(str.strip())


