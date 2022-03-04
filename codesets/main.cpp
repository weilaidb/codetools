#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "ctextcodecpub.h"
#include "supertest.h"
//#include "testui.h"

//#ifndef GMOCKTEST
//int main(int argc, char *argv[])
//{
//    CTextCodecPub::setTextCodecUtf8();
//    QApplication a(argc, argv);
//#if 1
//    MainWindow w(argv[0]);
//    w.show();
//#else
//    SuperTest w;
//    w.show();

//    //    testui w;
//    //    w.show();
//#endif


//    return a.exec();
//}

//#endif


#if 0
#include "cstringpub.h"
#include "cswitchpub.h"
#include "clogswpub.h"

int main(int argc, char **argv)
{
    qDebug() << "hello";
    unsigned char uacBuf[10] = {0xee,0xaa,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbe};
    qDebug() << CStringPub::GetStrOfData(uacBuf,10);

    diagShowDrvSw ();
    diagShowLogSw();

    return 0;
}


#endif
