# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'D:\E\QtExamplenew\codetools_py\ui\mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        icon = QtGui.QIcon.fromTheme("title.ico")
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.splitter_3 = QtWidgets.QSplitter(self.centralwidget)
        self.splitter_3.setOrientation(QtCore.Qt.Vertical)
        self.splitter_3.setObjectName("splitter_3")
        self.splitter = QtWidgets.QSplitter(self.splitter_3)
        self.splitter.setOrientation(QtCore.Qt.Horizontal)
        self.splitter.setObjectName("splitter")
        self.textEdit = QtWidgets.QTextEdit(self.splitter)
        self.textEdit.setObjectName("textEdit")
        self.textBrowser = QtWidgets.QTextBrowser(self.splitter)
        self.textBrowser.setObjectName("textBrowser")
        self.splitter_2 = QtWidgets.QSplitter(self.splitter_3)
        self.splitter_2.setOrientation(QtCore.Qt.Horizontal)
        self.splitter_2.setObjectName("splitter_2")
        self.textEdit_cfgTips = QtWidgets.QTextEdit(self.splitter_2)
        self.textEdit_cfgTips.setObjectName("textEdit_cfgTips")
        self.textEdit_cfgBefore = QtWidgets.QTextEdit(self.splitter_2)
        self.textEdit_cfgBefore.setObjectName("textEdit_cfgBefore")
        self.textEdit_cfgAfter = QtWidgets.QTextEdit(self.splitter_2)
        self.textEdit_cfgAfter.setObjectName("textEdit_cfgAfter")
        self.gridLayout.addWidget(self.splitter_3, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 23))
        self.menubar.setObjectName("menubar")
        self.menuAyStle = QtWidgets.QMenu(self.menubar)
        self.menuAyStle.setObjectName("menuAyStle")
        self.menu = QtWidgets.QMenu(self.menuAyStle)
        self.menu.setObjectName("menu")
        self.menuConfig = QtWidgets.QMenu(self.menu)
        self.menuConfig.setObjectName("menuConfig")
        self.menu_codeFormat_Recent = QtWidgets.QMenu(self.menu)
        self.menu_codeFormat_Recent.setObjectName("menu_codeFormat_Recent")
        self.menu_2 = QtWidgets.QMenu(self.menubar)
        self.menu_2.setObjectName("menu_2")
        self.menu_3 = QtWidgets.QMenu(self.menubar)
        self.menu_3.setObjectName("menu_3")
        self.menu_4 = QtWidgets.QMenu(self.menubar)
        self.menu_4.setObjectName("menu_4")
        self.menu_document_open_recent = QtWidgets.QMenu(self.menu_4)
        self.menu_document_open_recent.setObjectName("menu_document_open_recent")
        self.menu_document_search_recent = QtWidgets.QMenu(self.menu_4)
        self.menu_document_search_recent.setObjectName("menu_document_search_recent")
        self.menu_5 = QtWidgets.QMenu(self.menubar)
        self.menu_5.setObjectName("menu_5")
        self.menu_6 = QtWidgets.QMenu(self.menu_5)
        self.menu_6.setObjectName("menu_6")
        self.menu_7 = QtWidgets.QMenu(self.menu_5)
        self.menu_7.setObjectName("menu_7")
        self.menu_8 = QtWidgets.QMenu(self.menubar)
        self.menu_8.setObjectName("menu_8")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.toolBar = QtWidgets.QToolBar(MainWindow)
        self.toolBar.setObjectName("toolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)
        self.action_codeFormat_File = QtWidgets.QAction(MainWindow)
        self.action_codeFormat_File.setObjectName("action_codeFormat_File")
        self.action_codeFormat_Directory = QtWidgets.QAction(MainWindow)
        self.action_codeFormat_Directory.setObjectName("action_codeFormat_Directory")
        self.action_codeFormat_Edit_Config = QtWidgets.QAction(MainWindow)
        self.action_codeFormat_Edit_Config.setObjectName("action_codeFormat_Edit_Config")
        self.action_codeFormat_Save_Config = QtWidgets.QAction(MainWindow)
        self.action_codeFormat_Save_Config.setObjectName("action_codeFormat_Save_Config")
        self.action_codeFormat_Del_Config = QtWidgets.QAction(MainWindow)
        self.action_codeFormat_Del_Config.setObjectName("action_codeFormat_Del_Config")
        self.actionOpenFiles = QtWidgets.QAction(MainWindow)
        self.actionOpenFiles.setObjectName("actionOpenFiles")
        self.action_about = QtWidgets.QAction(MainWindow)
        self.action_about.setObjectName("action_about")
        self.actionfd = QtWidgets.QAction(MainWindow)
        self.actionfd.setObjectName("actionfd")
        self.action_mysql_testdatabase = QtWidgets.QAction(MainWindow)
        self.action_mysql_testdatabase.setObjectName("action_mysql_testdatabase")
        self.action_office_open = QtWidgets.QAction(MainWindow)
        self.action_office_open.setObjectName("action_office_open")
        self.action_office_search_file = QtWidgets.QAction(MainWindow)
        self.action_office_search_file.setObjectName("action_office_search_file")
        self.actionfd_2 = QtWidgets.QAction(MainWindow)
        self.actionfd_2.setObjectName("actionfd_2")
        self.action1 = QtWidgets.QAction(MainWindow)
        self.action1.setObjectName("action1")
        self.action_office_search_dir = QtWidgets.QAction(MainWindow)
        self.action_office_search_dir.setObjectName("action_office_search_dir")
        self.action_net_client = QtWidgets.QAction(MainWindow)
        self.action_net_client.setObjectName("action_net_client")
        self.action_net_server = QtWidgets.QAction(MainWindow)
        self.action_net_server.setObjectName("action_net_server")
        self.action_net_publish = QtWidgets.QAction(MainWindow)
        self.action_net_publish.setObjectName("action_net_publish")
        self.action_net_subscribe = QtWidgets.QAction(MainWindow)
        self.action_net_subscribe.setObjectName("action_net_subscribe")
        self.action_EditCfgFile = QtWidgets.QAction(MainWindow)
        self.action_EditCfgFile.setCheckable(True)
        self.action_EditCfgFile.setChecked(False)
        self.action_EditCfgFile.setObjectName("action_EditCfgFile")
        self.action_SwitchClearLeftText = QtWidgets.QAction(MainWindow)
        self.action_SwitchClearLeftText.setCheckable(True)
        self.action_SwitchClearLeftText.setObjectName("action_SwitchClearLeftText")
        self.action_TryAgain = QtWidgets.QAction(MainWindow)
        self.action_TryAgain.setObjectName("action_TryAgain")
        self.action_DeleteCfgFile = QtWidgets.QAction(MainWindow)
        self.action_DeleteCfgFile.setCheckable(True)
        self.action_DeleteCfgFile.setEnabled(True)
        self.action_DeleteCfgFile.setObjectName("action_DeleteCfgFile")
        self.action_ClipBoarChange = QtWidgets.QAction(MainWindow)
        self.action_ClipBoarChange.setCheckable(True)
        self.action_ClipBoarChange.setObjectName("action_ClipBoarChange")
        self.action_attention = QtWidgets.QAction(MainWindow)
        self.action_attention.setObjectName("action_attention")
        self.action_checknoexistpath = QtWidgets.QAction(MainWindow)
        self.action_checknoexistpath.setCheckable(True)
        self.action_checknoexistpath.setObjectName("action_checknoexistpath")
        self.menuConfig.addAction(self.action_codeFormat_Edit_Config)
        self.menuConfig.addAction(self.action_codeFormat_Save_Config)
        self.menuConfig.addAction(self.action_codeFormat_Del_Config)
        self.menu.addAction(self.action_codeFormat_File)
        self.menu.addAction(self.action_codeFormat_Directory)
        self.menu.addAction(self.menuConfig.menuAction())
        self.menu.addAction(self.menu_codeFormat_Recent.menuAction())
        self.menuAyStle.addAction(self.menu.menuAction())
        self.menu_2.addAction(self.action_about)
        self.menu_2.addAction(self.action_attention)
        self.menu_3.addAction(self.action_mysql_testdatabase)
        self.menu_4.addAction(self.action_office_open)
        self.menu_4.addAction(self.action_office_search_file)
        self.menu_4.addAction(self.action_office_search_dir)
        self.menu_4.addAction(self.menu_document_open_recent.menuAction())
        self.menu_4.addAction(self.menu_document_search_recent.menuAction())
        self.menu_6.addAction(self.action_net_server)
        self.menu_6.addAction(self.action_net_client)
        self.menu_7.addAction(self.action_net_publish)
        self.menu_7.addAction(self.action_net_subscribe)
        self.menu_5.addAction(self.menu_6.menuAction())
        self.menu_5.addAction(self.menu_7.menuAction())
        self.menu_8.addAction(self.action_EditCfgFile)
        self.menu_8.addAction(self.action_SwitchClearLeftText)
        self.menu_8.addAction(self.action_TryAgain)
        self.menu_8.addAction(self.action_DeleteCfgFile)
        self.menu_8.addAction(self.action_ClipBoarChange)
        self.menu_8.addAction(self.action_checknoexistpath)
        self.menubar.addAction(self.menuAyStle.menuAction())
        self.menubar.addAction(self.menu_3.menuAction())
        self.menubar.addAction(self.menu_4.menuAction())
        self.menubar.addAction(self.menu_5.menuAction())
        self.menubar.addAction(self.menu_8.menuAction())
        self.menubar.addAction(self.menu_2.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "代码集"))
        self.textEdit_cfgTips.setPlaceholderText(_translate("MainWindow", "配置的提示内容"))
        self.textEdit_cfgBefore.setPlaceholderText(_translate("MainWindow", "正则表达式前"))
        self.textEdit_cfgAfter.setPlaceholderText(_translate("MainWindow", "正则表达式后"))
        self.menuAyStle.setTitle(_translate("MainWindow", "优化"))
        self.menu.setTitle(_translate("MainWindow", "代码格式化"))
        self.menuConfig.setTitle(_translate("MainWindow", "配置"))
        self.menu_codeFormat_Recent.setTitle(_translate("MainWindow", "最近打开"))
        self.menu_2.setTitle(_translate("MainWindow", "帮助"))
        self.menu_3.setTitle(_translate("MainWindow", "数据库"))
        self.menu_4.setTitle(_translate("MainWindow", "文档"))
        self.menu_document_open_recent.setTitle(_translate("MainWindow", "最近打开"))
        self.menu_document_search_recent.setTitle(_translate("MainWindow", "最近查找"))
        self.menu_5.setTitle(_translate("MainWindow", "网络"))
        self.menu_6.setTitle(_translate("MainWindow", "测试"))
        self.menu_7.setTitle(_translate("MainWindow", "发布/订阅"))
        self.menu_8.setTitle(_translate("MainWindow", "配置操作"))
        self.toolBar.setWindowTitle(_translate("MainWindow", "toolBar"))
        self.action_codeFormat_File.setText(_translate("MainWindow", "文件"))
        self.action_codeFormat_Directory.setText(_translate("MainWindow", "文件夹"))
        self.action_codeFormat_Edit_Config.setText(_translate("MainWindow", "编辑"))
        self.action_codeFormat_Save_Config.setText(_translate("MainWindow", "保存"))
        self.action_codeFormat_Del_Config.setText(_translate("MainWindow", "删除"))
        self.actionOpenFiles.setText(_translate("MainWindow", "OpenFiles"))
        self.action_about.setText(_translate("MainWindow", "关于"))
        self.actionfd.setText(_translate("MainWindow", "fd"))
        self.action_mysql_testdatabase.setText(_translate("MainWindow", "测试"))
        self.action_office_open.setText(_translate("MainWindow", "打开"))
        self.action_office_search_file.setText(_translate("MainWindow", "查找文件"))
        self.actionfd_2.setText(_translate("MainWindow", "fd"))
        self.action1.setText(_translate("MainWindow", "1"))
        self.action_office_search_dir.setText(_translate("MainWindow", "查找文件夹"))
        self.action_net_client.setText(_translate("MainWindow", "客户端"))
        self.action_net_server.setText(_translate("MainWindow", "服务端"))
        self.action_net_publish.setText(_translate("MainWindow", "发布"))
        self.action_net_subscribe.setText(_translate("MainWindow", "订阅"))
        self.action_EditCfgFile.setText(_translate("MainWindow", "编辑配置文件"))
        self.action_EditCfgFile.setShortcut(_translate("MainWindow", "Ctrl+S"))
        self.action_SwitchClearLeftText.setText(_translate("MainWindow", "切换清除左侧内容"))
        self.action_SwitchClearLeftText.setShortcut(_translate("MainWindow", "Ctrl+W"))
        self.action_TryAgain.setText(_translate("MainWindow", "TryAgain"))
        self.action_TryAgain.setShortcut(_translate("MainWindow", "Ctrl+R"))
        self.action_DeleteCfgFile.setText(_translate("MainWindow", "删除配置文件"))
        self.action_DeleteCfgFile.setShortcut(_translate("MainWindow", "Ctrl+D"))
        self.action_ClipBoarChange.setText(_translate("MainWindow", "自动检测剪切板"))
        self.action_attention.setText(_translate("MainWindow", "注意事项"))
        self.action_checknoexistpath.setText(_translate("MainWindow", "过滤不存在的路径"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

