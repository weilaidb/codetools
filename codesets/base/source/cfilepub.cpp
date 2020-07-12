#include "cfilepub.h"

#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <qapplication.h>
#include "debugApp.h"
#include "cstringpub.h"

CFilePub::CFilePub()
{

}

int CFilePub::isFile(QString filename)
{
    QFileInfo fileinfo(filename);
    if(fileinfo.isFile())
    {
        return true;
    }
    return false;
}

int CFilePub::isDir(QString filename)
{
    QFileInfo fileinfo(filename);
    if(fileinfo.isDir())
    {
        return true;
    }
    return false;
}



int CFilePub::fileExist(QString filename)
{
    QFile file(filename);
    if(file.exists())
    {
        return true;
    }
    return false;
}

bool CFilePub::createFileNoExist(QString filename)
{
    if(fileExist(filename))
    {
        return true;
    }

    QDir dir(filename);
    bool ok =  createDirNoExist(dir.dirName());
    writeFileOnlly(filename, CStringPub::emptyString());
    return ok;
}

bool CFilePub::createDirNoExist(QString dirname)
{
    QDir dir(dirname);
    bool ok = dir.mkpath(dirname);//创建多级目录
    return ok;
}

QString CFilePub::readFileAll(QString filename)
{
    QString result("");
    QFile file(filename);
    if(!file.exists())
    {
        return result;
    }
    file.open(QIODevice::ReadOnly);
    result = file.readAll();
    file.close();

    return result;
}

QString CFilePub::writeFileOnlly(QString filename, QString msg)
{
    QString result("");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return result;
    }
    result = file.write(msg.toLocal8Bit().data());
    file.close();

    return msg;
}


QString CFilePub::writeFileAppend(QString filename, QString msg)
{
    QString result("");
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Append))
    {
        return result;
    }
    result = file.write(msg.toLocal8Bit().data());
    file.close();

    return msg;
}


QString CFilePub::writeFileWR(QString filename, QString msg)
{
    QString result("");
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
    {
        return result;
    }
    result = file.write(msg.toLocal8Bit().data());
    file.close();

    return msg;
}


QString CFilePub::deleteFile(QString filename)
{
    QString result("");
    QFile file(filename);
    if(!file.exists())
    {
        return result;
    }
    file.remove();
    file.close();

    return result;
}


QStringList CFilePub::getFileNames(QStringList nameFilters, const QString path)
{
    QDir dir(path);
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}

/**
 * @brief CFilePub::getFileAbsoluteNames 获取文件夹路径下的一级文件列表
 * @param nameFilters
 * @param path
 * @return
 */
QStringList CFilePub::getFileAbsoluteNames(QStringList nameFilters, const QString path)
{
    QDir dir(path);
    QStringList files;
    files.clear();
    QFileInfoList infolist = dir.entryInfoList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    foreach (QFileInfo info, infolist) {
        files += info.absolutePath() + QDir::separator() + info.fileName();
    }
    return files;
}
/**
 * @brief CFilePub::getFileAllAbsoluteNames 获取文件夹路径下的所有文件列表（递归）？
 * @param nameFilters
 * @param path
 * @return
 */
QStringList CFilePub::getFileAllAbsoluteNames(QStringList nameFilters, const QString filePath)
{
    QStringList files;
    files.clear();
    QFileInfoList infolist = getAllFileList(nameFilters, filePath);
//    debugApp() << "infolist:" << infolist.size();
    foreach (QFileInfo info, infolist) {
        files += info.absolutePath() + QDir::separator() + info.fileName();
    }

    return files;
}

/**
 * @brief CFilePub::getAllFileList 遍历文件文件夹信息列表
 * @param nameFilters
 * @param path
 * @return 遍历的所有文件信息列表
 */
QFileInfoList CFilePub::getAllFileList(QStringList nameFilters, QString path)
{
    QDir dir(path);
    QFileInfoList file_list   = dir.entryInfoList(nameFilters, QDir::Files| QDir::NoSymLinks|QDir::Readable|QDir::Writable, QDir::Name);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

//    debugApp() << "dirpath    :" << path;
//    debugApp() << "file_list  :" << file_list.size();
//    debugApp() << "folder_list:" << folder_list.size();

    for(int i = 0; i != folder_list.size(); i++)
    {
        qApp->processEvents();
        QString name = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = getAllFileList(nameFilters, name);
        file_list.append(child_file_list);
    }

    return file_list;
}

QStringList CFilePub::getOpenDiagFiles(QString &openFilePathRecent,QString filter)
{
    QStringList openfiles;
    /*打开一个dialog对话框，选择一个文件*/
    openfiles = QFileDialog::getOpenFileNames(nullptr, "请选择文件"
            , openFilePathRecent
            , filter);
    if(openfiles.isEmpty())
    {
        return openfiles;
    }
    debugApp() << "Open Files:" << openfiles;
    return  openfiles;
}

QStringList CFilePub::getOpenDiagFilesRecent(QString &openFilePathRecent,QString filter)
{
    QStringList openfiles;
    /*打开一个dialog对话框，选择一个文件*/
    openfiles = QFileDialog::getOpenFileNames(nullptr, "请选择文件"
                                              , openFilePathRecent
                                              , filter);
    if(openfiles.isEmpty())
    {
        return openfiles;
    }
    openFilePathRecent = openfiles.at(0);
    debugApp() << "Open Files:" << openfiles;
    return  openfiles;
}


QString CFilePub::getExistDir(QString tips, QString &recent)
{
    QString openDirPath = QFileDialog::getExistingDirectory(
                nullptr, tips,
                recent);
    if (openDirPath.isEmpty())
    {
        return CStringPub::emptyString();
    }
    recent = openDirPath;
    openDirPath += "/";
    return openDirPath;
}


QStringList CFilePub::getExistDirAllFiles(QString tips, QString &recent, QStringList &recentlist, QStringList nameFilters)
{
    QString  openDirPath = getExistDir(tips,recent);
    if(openDirPath.trimmed().isEmpty())
    {
        return CStringPub::emptyStringList();
    }
    recent = openDirPath;
    debugApp() << "Open Dir:" << openDirPath;
    recentlist.append(openDirPath);
    QStringList openfiles = CFilePub::getFileAllAbsoluteNames(nameFilters, openDirPath);
    return openfiles;
}

