#include "csystempub.h"
#include <QTextCodec>

CSystemPub::CSystemPub()
{

}

void CSystemPub::execCmd(const char *command)
{
    if(command == NULL) return ;
    /**
WinExec 的windows 调用，可以通过参数SW_HIDE隐藏命令行黑窗口
并且命令的路径是可以带括号的
*/
//    WinExec(command,SW_HIDE);
    ShellExecuteA (NULL,"open",command,NULL,NULL,SW_SHOW);
}

void CSystemPub::setCodecGBK()
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); //设置GBK到本地

}

void CSystemPub::setCodecUTF_8()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); //设置UTF-8到本地
}
