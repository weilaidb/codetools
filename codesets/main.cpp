#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "ctextcodecpub.h"
#include "supertest.h"
#include "testui.h"

#if 1
int main(int argc, char *argv[])
{
    CTextCodecPub::setTextCodecUtf8();
    QApplication a(argc, argv);
#if 1
    MainWindow w(argv[0]);
    w.show();
#else
    SuperTest w;
    w.show();

    //    testui w;
    //    w.show();
#endif


    return a.exec();
}

#else
int main(int argc, char **argv)
{
    qDebug() << "hello";
    return 0;
}


#endif
