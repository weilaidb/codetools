#ifndef CTEXTCODECPUB_H
#define CTEXTCODECPUB_H

#include <QString>



class CTextCodecPub
{
public:
    CTextCodecPub();
    static void setTextCodecUtf8();
    static void setTextCodecGBK();
    static void setTextCodecGB18030();
    static QString unicodeToUtf8(const QString& unicode);
    //text codec
    static char*  convertQString2buf(QString single, char *szLogin);
    static void setQTextCodecGBK();
    static void setQTextCodecUTF8();

};

#endif // CTEXTCODECPUB_H
