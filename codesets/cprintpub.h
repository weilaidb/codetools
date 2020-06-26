#ifndef CPRINTPUB_H
#define CPRINTPUB_H

#include <QtDebug>
#include <QMutex>
#include <QDateTime>
#include <QFile>

class CPrintPub
{
public:
    CPrintPub();
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    static void printToFile(QString fileName);
    static void canclePrintToFile();

private:
    static QString m_filename;
};

#endif // CPRINTPUB_H
