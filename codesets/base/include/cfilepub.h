#ifndef CFILEPUB_H
#define CFILEPUB_H

#include <QStringList>
#include <QFile>
#include <QDir>


class CFilePub
{
public:
    CFilePub();
    static int isFile(QString filename);
    static int isDir(QString filename);
    static int fileExist(QString filename);
    static QString readFileAll(QString filename);
    static QString writeFileOnlly(QString filename, QString msg);
    static QString writeFileAppend(QString filename, QString msg);
    static QString writeFileWR(QString filename, QString msg);
    static QString deleteFile(QString filename);
    static QStringList getFileNames(QStringList nameFilters, const QString path);
    static QStringList getFileAbsoluteNames(QStringList nameFilters, const QString path);
    static QStringList getFileAllAbsoluteNames(QStringList nameFilters, const QString filePath);
    static QFileInfoList getAllFileList(QStringList nameFilters, QString path);
//file dialog
    static QStringList getOpenDiagFiles(QString &openFilePathRecent, QString filter);
    static QStringList getOpenDiagFilesRecent(QString &openFilePathRecent, QString filter);
};

#endif // CFILEPUB_H
