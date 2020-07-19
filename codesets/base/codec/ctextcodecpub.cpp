#include "ctextcodecpub.h"

#include <QTextCodec>

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

