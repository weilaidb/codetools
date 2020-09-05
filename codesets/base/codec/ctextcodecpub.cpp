#include "ctextcodecpub.h"

#include <QTextCodec>
#ifdef WIN32
#include <cexpresspub.h>
#include <cstringpub.h>
#include <windows.h>
#endif

CTextCodecPub::CTextCodecPub()
{

}

void CTextCodecPub::setTextCodecUtf8()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
}

void CTextCodecPub::setTextCodecGBK()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
}

void CTextCodecPub::setTextCodecGB18030()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb18030"));
}

QString CTextCodecPub::unicodeToUtf8(const QString& unicode)
{
    QString result;
    int index = unicode.indexOf("\\u");
    while (index != -1)
    {
        QString s1 = unicode.mid(index + 2, 4);
        result.append(s1.toUShort(0, 16));
        index = unicode.indexOf("\\u", index+5);
    }
    return result.toUtf8().constData();
}


void CTextCodecPub::setQTextCodecGBK()
{
    QTextCodec *textc_gbk = QTextCodec::codecForName("gb18030");
    QTextCodec::setCodecForLocale(textc_gbk);
}

void CTextCodecPub::setQTextCodecUTF8()
{
    QTextCodec *textc_utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(textc_utf8);
}




char*  CTextCodecPub::convertQString2buf(QString single, char *szLogin)
{
    //    QTextCodec *textc_gbk = QTextCodec::codecForName("gb18030");
    QTextCodec *textc_utf8 = QTextCodec::codecForName("UTF-8");

#ifdef WIN32
//    LPCSTR filepath2 = NULL;
    /**
      ** 统一使用默认使用的字符编码为utf-8
      ** 发送的数据也是utf-8
      ** QString是Unicode编码，将此
      ** unicode -> gbk
      **/
    //此处会导致Release版本异常退出,原来的是textc_gbk解码的
    //原来的数据是UTF-8数据,需要转换成GBK才能查找到
    QByteArray ba111 = textc_utf8->fromUnicode(single); // strUser是QString，外部传来的数据。

    //先转换成Unicode
    QString utf8data = QString::fromUtf8(ba111);
    //再由Unicode转换成GBK
    //textc_gbk->fromUnicode接口存在崩溃的问题，因此使用setQTextCodecGBK先变更一下。再回退原来的编码setQTextCodecUTF8
    //    char* temp111 = textc_gbk->fromUnicode(utf8data).data();
    setQTextCodecGBK();
    QByteArray ba222 = utf8data.toLocal8Bit();
    setQTextCodecUTF8();
    char* temp111 = ba222.data();
//    PrintStrData("temp111", (BYTE *)temp111, strlen(temp111));

    strcpy(szLogin, temp111);
//    //    然后强行转换char*到LPCWSTR：
//    filepath2 = (LPCSTR)szLogin;
#endif


    return szLogin;
}
//GBK转Unicode编码
QString CTextCodecPub::getGBKToUnicode(char *text)
{
    if(CExpressPub::isNullPtr(text))
    {
        return CStringPub::emptyString();
    }
    return getGBKTextCodec()->toUnicode(text);
}


//GBK转Unicode编码
QString CTextCodecPub::getUtf8ToUnicode(char *text)
{
    return getUtf8TextCodec()->toUnicode(text);
}


QTextCodec *CTextCodecPub::getUtf8TextCodec()
{
    return QTextCodec::codecForName("UTF-8");
}

QTextCodec *CTextCodecPub::getGBKTextCodec()
{
    return QTextCodec::codecForName("gb18030");
}

