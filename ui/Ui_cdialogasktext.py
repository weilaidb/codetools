# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'D:\E\QtExamplenew\codetools_py\ui\cdialogasktext.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_CDialogAskText(object):
    def setupUi(self, CDialogAskText):
        CDialogAskText.setObjectName("CDialogAskText")
        CDialogAskText.resize(257, 175)
        self.gridLayout = QtWidgets.QGridLayout(CDialogAskText)
        self.gridLayout.setObjectName("gridLayout")
        self.splitter_2 = QtWidgets.QSplitter(CDialogAskText)
        self.splitter_2.setOrientation(QtCore.Qt.Vertical)
        self.splitter_2.setObjectName("splitter_2")
        self.label = QtWidgets.QLabel(self.splitter_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setMinimumSize(QtCore.QSize(0, 30))
        self.label.setMaximumSize(QtCore.QSize(16777215, 30))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(14)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.splitter = QtWidgets.QSplitter(self.splitter_2)
        self.splitter.setOrientation(QtCore.Qt.Horizontal)
        self.splitter.setObjectName("splitter")
        self.textEdit = QtWidgets.QTextEdit(self.splitter)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.textEdit.sizePolicy().hasHeightForWidth())
        self.textEdit.setSizePolicy(sizePolicy)
        self.textEdit.setMinimumSize(QtCore.QSize(0, 60))
        self.textEdit.setMaximumSize(QtCore.QSize(16777215, 60))
        self.textEdit.setObjectName("textEdit")
        self.widget = QtWidgets.QWidget(self.splitter)
        self.widget.setObjectName("widget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.widget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.pushButton_paste = QtWidgets.QPushButton(self.widget)
        self.pushButton_paste.setMinimumSize(QtCore.QSize(0, 30))
        self.pushButton_paste.setMaximumSize(QtCore.QSize(16777215, 60))
        self.pushButton_paste.setObjectName("pushButton_paste")
        self.verticalLayout.addWidget(self.pushButton_paste)
        self.pushButton_clear = QtWidgets.QPushButton(self.widget)
        self.pushButton_clear.setMinimumSize(QtCore.QSize(0, 30))
        self.pushButton_clear.setMaximumSize(QtCore.QSize(16777215, 60))
        self.pushButton_clear.setObjectName("pushButton_clear")
        self.verticalLayout.addWidget(self.pushButton_clear)
        self.gridLayout.addWidget(self.splitter_2, 0, 0, 1, 1)
        self.buttonBox = QtWidgets.QDialogButtonBox(CDialogAskText)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.gridLayout.addWidget(self.buttonBox, 1, 0, 1, 1)

        self.retranslateUi(CDialogAskText)
        self.buttonBox.accepted.connect(CDialogAskText.accept)
        self.buttonBox.rejected.connect(CDialogAskText.reject)
        QtCore.QMetaObject.connectSlotsByName(CDialogAskText)

    def retranslateUi(self, CDialogAskText):
        _translate = QtCore.QCoreApplication.translate
        CDialogAskText.setWindowTitle(_translate("CDialogAskText", "Dialog"))
        self.label.setText(_translate("CDialogAskText", "请输入查询的内容"))
        self.pushButton_paste.setText(_translate("CDialogAskText", "粘贴"))
        self.pushButton_clear.setText(_translate("CDialogAskText", "清除"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    CDialogAskText = QtWidgets.QDialog()
    ui = Ui_CDialogAskText()
    ui.setupUi(CDialogAskText)
    CDialogAskText.show()
    sys.exit(app.exec_())

