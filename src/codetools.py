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


            for i in range(len(menulist)):
                print(menulist[i])
                self.generateMenu.addAction(menulist[i])
            # self.rightPopMenu.addAction('item1')
            # self.rightPopMenu.addAction('item2')
            # self.rightPopMenu.addSeparator()
            # self.rightPopMenu.addAction('item3')
            self.rightPopMenu.triggered.connect(self._triggered)
            self.rightPopMenu.exec(self.cursor().pos())
        except Exception as e:
            print("exception:%s" %e)
            return e


    def _triggered(self, action): #出发点击，快捷键等信号
            print(action.text())
    def keyPressEvent(self, e): #按键事件
        if (e.modifiers() == Qt.ControlModifier) and e.key() == Qt.Key_Q: #设置组合键事件
            print('触发组合键')