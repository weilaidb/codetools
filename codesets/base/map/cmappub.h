#ifndef CMAPPUB_H
#define CMAPPUB_H

#include <QMap>
#include <QString>
#include <QString>



class CMapPub
{
public:
    CMapPub();
    static void insertMapFileMode(QString str, QString val);
    static QMap<QString, QString> *getMapFileMode();


private:
    static QMap<QString, QString> m_tMapFileMode;
    static QMap<QString, QString> *getMapFileModeInstance()
    {
        return &m_tMapFileMode;
    }

};

#endif // CMAPPUB_H
