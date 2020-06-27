#include "cfilepub.h"

#include <QFile>
#include <QDir>
#include "debugApp.h"

CFilePub::CFilePub()
{

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
        QString name = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = getAllFileList(nameFilters, name);
        file_list.append(child_file_list);
    }

    return file_list;
}

