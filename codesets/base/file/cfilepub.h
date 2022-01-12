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
    static bool pathExist(QString filename);
    static bool pathNoExist(QString filename);
    static bool pathNoExistFileOrDir(QString filename);
    static QString dirName(QString filename);
    static QString baseName(QString filename);
    static bool createFileEmptyNoExist(QString filename);
    static bool createFileEmptyNoExistAndVar(QString &m_Var,QString filename);
    static bool createFileContentNoExist(QString filename, QString content);
    static bool createDirNoExist(QString dirname);
    static bool createDirExt(QString dirname);
    //copy
    static bool copyFile(QString filenameSrc,QString filenameDest);
    //rename
    static bool renameFile(QString filenameSrc,QString filenameDest);

    //删除文件夹及文件
    static bool deleteDirFiles(QString dirName);
    static bool deleteDirIfNoFiles(QString dirName);
    static bool deleteFileOrFolder(const QString &strPath);
    static bool checkFileExistLine(QString filename, QString line);
    static QString readFileAll(QString filename);
    static QStringList readFileAllFilterEmptyUnique(QString filename);
    static QStringList readFileAllFilterEmptyUniqueNoExistAndVar(QString &m_Var,QString filename);
    static QStringList readFileAllFilterEmptyUniqueSort(QString filename);
    static QStringList readFileAllFilterEmptyUniqueMulti(QString filename);
    static QString writeFileOnlly(QString filename, QString msg);
    static QString writeFileAppend(QString filename, QString msg);
    static QString writeFileWR(QString filename, QString msg);
    static QString writeFileWOnly(QString filename, QString msg);
    static QString writeFileWOnly(QString filename, QStringList list);
    static QString deleteFile(QString filename);
    static QString deleteFileSameLine(QString filename,QString same);
    static QString deleteFileSameLineExt(QString filename,QString same);
    static QStringList getFileNames(QStringList nameFilters, const QString path);
    static QStringList getFileAbsoluteNames(QStringList nameFilters, const QString path);
    static QStringList getFileAllAbsoluteNames(QStringList nameFilters, const QString filePath);
    static QStringList getFileAllRelateNames(QStringList nameFilters, const QString filePath);
    static QFileInfoList getAllFileList(QStringList nameFilters, QString path);

//file dialog
    static QStringList getOpenDiagFiles(QString &openFilePathRecent, QString filter);
    static QStringList getOpenDiagFilesRecent(QString &openFilePathRecent, QString filter);
    static QString getExistDir(QString tips, QString &recent);
    static QStringList getExistDirAllFiles(QString tips, QString &recent, QStringList &recentlist, QStringList nameFilters);
    static QString getCurrentPath();
    static QString getCurrentPath(QString filename);
    static QString getSeparator();
    static QString toNativeSeparators(QString filePath);
    static void openSystemPathOrUrl(QString filenameOrUrl);
    static quint64 dirFileSize(const QString path);
    static qint64 fileSize(const QString path);
    static QString parentDir(QString filepath);

    //const dir path
    static QString applicationPath();
    static QString currentPath();
    static QString homePath();
    static QStringList homePaths();
    static QString myDocuPath();
    static QStringList myDocuPaths();
    static QString myDeskPath();
    static QStringList myDeskPaths();
    static QString appDataPath();
    static QStringList appDataPaths();
    static QString tempPath();
    static QStringList tempPaths();

    //const dir path
    static QString getBComparePath();

    //get in file's num
    static quint32 getNumFirstFromFile(QString filename);
    static quint32 getNumFirstFromFileLimitMin(QString filename,quint32 dwMax);
};

#endif // CFILEPUB_H
