#include "mainwindow.h"

#include <QApplication>
#include "ctextcodecpub.h"

int main(int argc, char *argv[])
{
    CTextCodecPub::setTextCodecGB18030();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
