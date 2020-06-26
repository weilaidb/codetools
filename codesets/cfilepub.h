#ifndef CFILEPUB_H
#define CFILEPUB_H

#include <QStringList>
#include <QFile>
#include <QDir>


class CFilePub
{
public:
    CFilePub();
    static QString readFileAll(QString filename);
    static QString writeFileOnlly(QString filename, QString msg);
    static QString writeFileAppend(QString filename, QString msg);
    static QString writeFileWR(QString filename, QString msg);
    static QString deleteFile(QString filename);
    static QStringList getFileNames(QStringList nameFilters, const QString path);
    static QStringList getFileAbsoluteNames(QStringList nameFilters, const QString path);
    static QStringList getFileAllAbsoluteNames(QStringList nameFilters, const QString filePath);
    static QFileInfoList getAllFileList(QStringList nameFilters, QString path);
};

#endif // CFILEPUB_H
