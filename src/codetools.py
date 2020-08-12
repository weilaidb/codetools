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

        #文件名称定义
        self.fileCumstomMenu = "reg\selfmenu.txt"


        ##右键菜单
        self.textEdit.setContextMenuPolicy(Qt.CustomContextMenu)  ######允许右键产生子菜单
        self.textEdit.customContextMenuRequested.connect(self.generateMenu_left)  ####右键菜单
        self.rightPopMenu = QtWidgets.QMenu()
        self.rightPopMenu.setObjectName("rightPopMenu")

    def generateMenu_left(self, pos):
        print("left menu")
        menulist = (readFileUtf8(self.fileCumstomMenu))
        # showlist(menulist)
        menulist = list(set(menulist))
        menulist.sort()

        try:
            self.rightPopMenu.clear()
            self.generateMenu = QtWidgets.QMenu("Generate")
            self.FreqUseCfgListMenu = QtWidgets.QMenu("常用配置列表")
            self.OpenCfgDirAction = QtWidgets.QAction("打开配置文件夹")
            self.OpenCfgFileAction = QtWidgets.QAction("打开配置总表")
            self.OpenCfgFileAction = QtWidgets.QAction("打开配置总表")
            # self.FreqUseCfgListMenu = QtWidgets.QMenu("常用配置列表")
            self.FileListsMenu = QtWidgets.QMenu("文件列表")

            self.clearAction = QtWidgets.QAction("清空")
            self.copyAction  = QtWidgets.QAction("复制")
            self.pasteAction = QtWidgets.QAction("粘贴")
            self.selectallcopyAction = QtWidgets.QAction("全选复制")

            self.rightPopMenu.addMenu(self.generateMenu)
            self.rightPopMenu.addMenu(self.FreqUseCfgListMenu)
            self.rightPopMenu.addAction(self.OpenCfgDirAction)
            self.rightPopMenu.addAction(self.OpenCfgFileAction)
            self.rightPopMenu.addMenu(self.FileListsMenu)

            self.rightPopMenu.addAction(self.clearAction)
            self.rightPopMenu.addAction(self.copyAction)
            self.rightPopMenu.addAction(self.pasteAction)
            self.rightPopMenu.addAction(self.selectallcopyAction)

            # #并不会添加5个
            # for i in range(5):
            #     self.rightPopMenu.addAction(self.copyAction)

            keych = "/"
            menutext = ""
            curpos = 0
            changed = 0
            num = 0
            self.keylist = []
            self.vallist = []
            for i in range(len(menulist)):
                item = menulist[i]
                pos = item.find(keych)

                print("---->>pos:%d %s" % (pos, item))
                # print(menulist[i])

                if(0 == len(item.strip())):
                    continue

                if(-1 == pos):
                    print("not found:%d" % pos)
                else:
                    print("found:%d" % pos)

                if(curpos != pos):
                    changed = 1
                    menutext = item[0:pos]
                    print("menutext:%s" % menutext)
                    curpos = pos

                if(changed):
                    print("changed!")
                    self.keylist.append(menutext)
                    self.vallist.append("")
                    self.vallist[num] += item + ";"
                    changed = 0
                    num+=1
                else:
                    print("no changed! item:%s" % item)
                    if(num > 0):
                        self.vallist[num - 1] += item + ";"

            for i in range(num):
                print(self.keylist)
                print(self.vallist)

            self.testMenu =  [QtWidgets.QMenu("")]
            showMenuMax = 1000
            for i in range(showMenuMax):
                self.testMenu.append(QtWidgets.QMenu(""))
            #

            self.testAction =  [QtWidgets.QAction("")]
            showActionMax = 10000
            for i in range(showActionMax):
                self.testAction.append(QtWidgets.QAction(""))
            #

            actioncount = 0
            for i in range(num):
                key = self.keylist[i]
                vallist = self.vallist[i].split(";")

                self.testMenu[i] = QtWidgets.QMenu(key)
                print("create menu key:%s" % key)
                for j in range(len(vallist)):
                    showval = vallist[j].strip()
                    if(0 == len(showval)):
                        continue
                    print("create action:%s" % showval)

                    self.testAction[actioncount] = QtWidgets.QAction(showval)
                    self.testMenu[i].addAction(self.testAction[actioncount])
                    actioncount+=1

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