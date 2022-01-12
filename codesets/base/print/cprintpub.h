#ifndef CPRINTPUB_H
#define CPRINTPUB_H

#include <QStringList>



class CPrintPub
{
public:
    CPrintPub();
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    static void printToFile(QString fileName);
    static void canclePrintToFile();

    static void printArray(char **argv, int size);

    static void printStringList(QStringList list);
    static void printStringListTip(QStringList list, QString tip);
    static void printString(QString str);
    static void printStringData(QString str);
    static void printStringTip(QString str, QString tip);
private:
    static QString m_filename;


};

#endif // CPRINTPUB_H
