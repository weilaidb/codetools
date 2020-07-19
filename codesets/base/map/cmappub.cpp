#include "cmappub.h"
#include "debugApp.h"

QMap<QString, QString> CMapPub::m_tMapFileMode;
CMapPub::CMapPub()
{

}

void CMapPub::insertMapFileMode(QString str, QString val)
{
    getMapFileModeInstance()->insert(str,val);
//    debugApp() << "getMapFileModeInstance()->size():" << getMapFileModeInstance()->size();

}

QMap<QString, QString> *CMapPub::getMapFileMode()
{
    return getMapFileModeInstance();
}
