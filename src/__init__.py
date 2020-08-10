# -*- coding: utf-8 -*-
from codetools import *

if __name__ == '__main__':
    print("hello world")
    import sys
    from PyQt5.QtWidgets import QApplication
    app = QApplication(sys.argv)
    ftpw = MainWindow()
    ftpw.show()
    app.installEventFilter(ftpw)
    sys.exit(app.exec_())
