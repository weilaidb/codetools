#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "ctextcodecpub.h"

#if 1
int main(int argc, char *argv[])
{
    CTextCodecPub::setTextCodecUtf8();
    QApplication a(argc, argv);
    MainWindow w(argv[0]);
    w.show();
    return a.exec();
}
#endif
