#ifndef CMAPPUB_H
#define CMAPPUB_H

#include <QMap>
#include <QString>
#include <QStringList>



class CMapPub
{
public:
    CMapPub();
    static void insertMapFileMode(QString str, QStringList list);
    static QMap<QString, QStringList> *getMapFileMode();


private:
    static QMap<QString, QStringList> m_tMapFileMode;
    static QMap<QString, QStringList> *getMapFileModeInstance()
    {
        return &m_tMapFileMode;
    }

};

#endif // CMAPPUB_H
