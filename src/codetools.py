# -*- coding: utf-8 -*-
import re
import os
import sys
import html
import time
import platform
import pyperclip
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *

sys.path.append('../ui/')
from Ui_mainwindow import *
sys.path.append('../base/')
from base import *


class MainWindow(QMainWindow, Ui_MainWindow):
    """
    Class documentation goes here.
    """
    def __init__(self, parent=None):
        """
        Constructor

        @param parent reference to the parent widget
        @type QWidget
        """
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        ##右键菜单
        self.textEdit.setContextMenuPolicy(Qt.CustomContextMenu)  ######允许右键产生子菜单
        self.textEdit.customContextMenuRequested.connect(self.generateMenu_left)  ####右键菜单
        self.rightPopMenu = QtWidgets.QMenu()
        self.rightPopMenu.setObjectName("rightPopMenu")

        self.topdir = "reg" + os.sep
        self.filename_normalfiles = self.topdir + "normalfiles.txt"
        self.filename_totalmenu = self.topdir + "selfmenu.txt"

    def appendActionFileList(self, par_filemenu):
        filelist = listuniquesort((readFileUtf8(self.filename_normalfiles)))
        filelistpos = 0
        for i in range(len(filelist)):
            self.filelistAction[filelistpos] = QtWidgets.QAction(filelist[i])
            par_filemenu.addAction(self.filelistAction[filelistpos])
            filelistpos+=1
        pass

    def addMenuOrActionMayPub(self, par_rightPopMenu):
        self.FreqUseCfgListMenu = QtWidgets.QMenu("常用配置列表")
        self.OpenCfgDirAction = QtWidgets.QAction("打开配置文件夹")
        self.OpenCfgFileAction = QtWidgets.QAction("打开配置总表")
        self.FileListsMenu = QtWidgets.QMenu("文件列表")
        self.appendActionFileList(self.FileListsMenu)

        self.clearAction = QtWidgets.QAction("清空")
        self.copyAction  = QtWidgets.QAction("复制")
        self.pasteAction = QtWidgets.QAction("粘贴")
        self.selectallcopyAction = QtWidgets.QAction("全选复制")

        self.FreqUseCfgListMenu.triggered.connect(self._triggered_FreqUseCfgListMenu )
        self.OpenCfgDirAction.triggered.connect(self._triggered_OpenCfgDirAction )
        self.OpenCfgFileAction.triggered.connect(self._triggered_OpenCfgFileAction )
        self.FileListsMenu.triggered.connect(self._triggered_FileListsMenu )
        self.clearAction.triggered.connect(self._triggered_clearAction )
        self.copyAction.triggered.connect(self._triggered_copyAction )
        self.pasteAction.triggered.connect(self._triggered_pasteAction )
        self.selectallcopyAction.triggered.connect(self._triggered_selectallcopyAction )

        par_rightPopMenu.addMenu(self.generateMenu)
        par_rightPopMenu.addMenu(self.FreqUseCfgListMenu)
        par_rightPopMenu.addAction(self.OpenCfgDirAction)
        par_rightPopMenu.addAction(self.OpenCfgFileAction)
        par_rightPopMenu.addMenu(self.FileListsMenu)

        par_rightPopMenu.addAction(self.clearAction)
        par_rightPopMenu.addAction(self.copyAction)
        par_rightPopMenu.addAction(self.pasteAction)
        par_rightPopMenu.addAction(self.selectallcopyAction)

    def _triggered_FreqUseCfgListMenu(self):
        pass

    def _triggered_OpenCfgDirAction(self):
        opencurrentcwd()
        pass

    def _triggered_OpenCfgFileAction(self):
        openfilelist = [self.filename_normalfiles , self.filename_totalmenu]
        for i in range(len(openfilelist)):
            print("filename_:%s" % getcwdwithpath(openfilelist[i]))
            openfileordirpath(getcwdwithpath(openfilelist[i]))
        pass

    def _triggered_FileListsMenu(self, action):
        print("file list triggered:%s" % action.text())
        openfileordirpath(action.text())
        pass

    def _triggered_clearAction(self):
        self.textEdit.clear()
        pass

    def _triggered_copyAction(self):
        pass

    def _triggered_pasteAction(self):
        pass

    def _triggered_selectallcopyAction(self):
        pass

    def initVar(self):
        self.keych = "/"
        self.menutext = ""
        self.curpos = 0
        self.changed = 0
        self.num = 0
        self.keylist = []
        self.vallist = []
        self.rightPopMenu.clear()
        self.actioncount = 0

        #the reserved qmenu max for use
        self.showMenuMax = 1000
        self.testMenu =  [QtWidgets.QMenu("")]
        for i in range(self.showMenuMax):
            self.testMenu.append(QtWidgets.QMenu(""))

        #the reserved qaction max for use
        self.showActionMax = 10000
        self.testAction =  [QtWidgets.QAction("")]
        for i in range(self.showActionMax):
            self.testAction.append(QtWidgets.QAction(""))

        #file list action
        self.filelistActionMax = 10000
        self.filelistAction =  [QtWidgets.QAction("")]
        for i in range(self.filelistActionMax):
            self.filelistAction.append(QtWidgets.QAction(""))


    def printkeyvallist(self):
        for i in range(self.num):
            print(self.keylist)
            print(self.vallist)

    def printfound(self, pos):
        if(-1 == pos):
            print("not found:%d" % pos)
        else:
            print("found:%d" % pos)

    def generateMenu_left(self, pos):
        print("left menu")
        try:
            menulist = listuniquesort((readFileUtf8(self.filename_totalmenu)))
            # showlist(menulist)
            self.initVar()
            self.generateMenu = QtWidgets.QMenu("Generate")
            self.addMenuOrActionMayPub(self.rightPopMenu)
            for i in range(len(menulist)):
                item = menulist[i]
                pos = item.find(self.keych)
                print("---->>pos:%d %s" % (pos, item))

                if(stringlenzero(item)):
                    continue
                self.printfound(pos)

                if(self.curpos != pos):
                    self.changed = 1
                    self.menutext = item[0:pos]
                    self.curpos = pos
                    print("menutext:%s" % self.menutext)

                if(self.changed):
                    self.keylist.append(self.menutext)
                    self.vallist.append("")
                    self.vallist[self.num] += item + ";"
                    self.changed = 0
                    self.num+=1
                    print("changed!")
                else:
                    print("no changed! item:%s" % item)
                    if(self.num > 0):
                        self.vallist[self.num - 1] += item + ";"

            self.printkeyvallist()
            for i in range(self.num):
                key = self.keylist[i]
                vallist = self.vallist[i].split(";")
                self.testMenu[i] = QtWidgets.QMenu(key)
                print("create menu key:%s" % key)
                for j in range(len(vallist)):
                    showval = vallist[j].strip()
                    if(stringlenzero(showval)):
                        continue
                    print("create action:%s" % showval)

                    self.testAction[self.actioncount] = QtWidgets.QAction(showval)
                    self.testMenu[i].addAction(self.testAction[self.actioncount])
                    self.actioncount+=1

                self.generateMenu.addMenu(self.testMenu[i])

            self.rightPopMenu.triggered.connect(self._triggered)
            self.rightPopMenu.exec(self.cursor().pos())
        except Exception as e:
            print("exception:%s" %e)
            return e


    def _triggered(self, action): #出发点击，快捷键等信号
        print("triggered:%s" % action.text())
    def keyPressEvent(self, e): #按键事件
        if (e.modifiers() == Qt.ControlModifier) and e.key() == Qt.Key_Q: #设置组合键事件
            print('触发组合键')