#include "csystempub.h"
#include <QProcess>
#include <QTextCodec>

char CSystemPub::szLogin[MAX_LENGTH] = {0};

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

void CSystemPub::execCmd(QString command)
{
    return execCmd(command.toLocal8Bit().data());
}

void CSystemPub::explorer(const char *command)
{
    HINSTANCE ret;
    if(command == NULL) return ;
    /**
WinExec 的windows 调用，可以通过参数SW_HIDE隐藏命令行黑窗口
并且命令的路径是可以带括号的
*/
    qDebug() << "command:" << command;
//    WinExec(command,SW_HIDE);
//    ShellExecuteA (NULL,"exporer",command,NULL,NULL,SW_SHOW);
//    ret = ShellExecuteA(NULL, "open", "cmd", command, NULL, SW_HIDE);
    ret = ShellExecuteA(NULL, "open", "cmd", command, NULL, SW_SHOW);
    qDebug() << "ret:" << ret;

}

char*  CSystemPub::convertQString2buf(QString single)
{
    QTextCodec *textc_gbk = QTextCodec::codecForName("gb18030");
    /**
      ** 统一使用默认使用的字符编码为utf-8
      ** 发送的数据也是utf-8
      **/
    QTextCodec *textc_utf8 = QTextCodec::codecForName("UTF-8");


    LPCSTR filepath2 = NULL;
    memset(szLogin, 0, MAX_LENGTH);
    qDebug() << "convertQString2buf single:" << single;

    /**
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
    setCodecGBK();

//    setQTextCodecGBK();
    QByteArray ba222 = utf8data.toLocal8Bit();
    setCodecUTF_8();
//    setQTextCodecUTF8();
    char* temp111 = ba222.data();
//    PrintStrData("temp111", (BYTE *)temp111, strlen(temp111));

    strcpy(szLogin, temp111);
    //    然后强行转换char*到LPCWSTR：
    filepath2 = (LPCSTR)szLogin;
    fprintf(stdout, "temp111  :%s\n", temp111);
    fprintf(stdout, "szLogin  :%s\n", szLogin);
    fprintf(stdout, "filepath2:%s\n", filepath2);
    fflush(stdout);
    return szLogin;
}

void CSystemPub::explorer(QString command)
{
    HINSTANCE ret;
    LPCSTR filepath2 = NULL;
    qDebug() << "command1:" << command;
//    return explorer(command.toLocal8Bit().data());
//    return explorer(command.toLatin1().data());

    filepath2 = convertQString2buf(command);
    qDebug() << "filepath2:" << filepath2;

//            //    ShellExecuteA(NULL,"open", exepath,filepath2,NULL,SW_SHOWNORMAL);
    ret = ShellExecuteA(NULL,"open", filepath2,NULL,NULL,SW_SHOWMAXIMIZED);
//            executecmd(single);
    qDebug() << "ret1:" << ret;
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

QString CSystemPub::getSystemEnvironment()
{
    return QProcessEnvironment::systemEnvironment().value("PATH");
}
