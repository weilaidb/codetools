#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "ctextcodecpub.h"
#include "tabwidget.h"

#if 1
int main(int argc, char *argv[])
{
    CTextCodecPub::setTextCodecUtf8();
    QApplication a(argc, argv);
#if 0
    MainWindow w(argv[0]);
    w.show();
#endif

    TabWidget t(argv[0]);
    t.show();

    return a.exec();
}

#else
int main(int argc, char **argv)
{
    qDebug() << "hello";
    return 0;
}


#endif
