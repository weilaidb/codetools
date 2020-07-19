#include "mainwindow.h"

#include <QApplication>
#include "ctextcodecpub.h"

int main(int argc, char *argv[])
{
    CTextCodecPub::setTextCodecUtf8();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
