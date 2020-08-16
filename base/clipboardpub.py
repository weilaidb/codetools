# -*- coding: utf-8 -*-

import pyperclip


def getclipboardtext():
    return pyperclip.paste()

def setclipboardtext(str):
    pyperclip.copy(str)
