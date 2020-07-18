#include "cmappub.h"
#include "debugApp.h"

QMap<QString, QStringList> CMapPub::m_tMapFileMode;
CMapPub::CMapPub()
{

}

void CMapPub::insertMapFileMode(QString str, QStringList list)
{
    getMapFileModeInstance()->insert(str,list);
    debugApp() << "getMapFileModeInstance()->size():" << getMapFileModeInstance()->size();

}

QMap<QString, QStringList> *CMapPub::getMapFileMode()
{
    return getMapFileModeInstance();
}
