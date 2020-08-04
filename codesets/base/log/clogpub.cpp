#include "clogpub.h"
#include "csignpub.h"
#include "debugApp.h"
#include "cstringpub.h"

#include <cfilepub.h>
#include <cprintpub.h>

QString CLogPub::m_logDefaultFileName = "app.log";

CLogPub::CLogPub()
{

}

void CLogPub::logDefault(QString info)
{
    info.append(CSignPub::signEnter());
    CFilePub::writeFileAppend(m_logDefaultFileName, info);
}

void CLogPub::msgDefault(QString info)
{
    info.append(CSignPub::signEnter());
    QByteArray ba = info.toLatin1();
    char *mm = ba.data();
//    debugApp()<< mm <<endl;  //调试时，在console中输出
    string cppstr = CStringPub::getDataOfStr((BYTE *)mm, strlen(mm));
//    cout << cppstr << endl;  //调试时，在console中输出
    CFilePub::writeFileAppend(m_logDefaultFileName, info);
    CFilePub::writeFileAppend(m_logDefaultFileName, cppstr.c_str());
}

void CLogPub::msgDefault(char *pMsg)
{
    QString result =CStringPub::emptyString();
    result.append(CSignPub::signEnter());
    result.append(CStringPub::hexToString((BYTE *)pMsg));
    CFilePub::writeFileAppend(m_logDefaultFileName, result);
}
