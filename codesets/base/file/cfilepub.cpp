#include "cfilepub.h"

#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <qapplication.h>
#include <csignpub.h>
#include <cstringpub.h>
#include <QDesktopServices>
#include <clogpub.h>
#include "debugApp.h"
#include "cstringpub.h"
#include "cexpresspub.h"
#include "csignpub.h"

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

void CFilePub::openSystemPathOrUrl(QString filenameOrUrl)
{
    //QUrl支持中文打开
    if(CFilePub::isFile(filenameOrUrl) || CFilePub::isDir(filenameOrUrl))
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filenameOrUrl));
        return;
    }
    bool ok = QDesktopServices::openUrl(QUrl(filenameOrUrl));
    Q_UNUSED(ok)
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

bool CFilePub::pathExist(QString filename)
{
    QFile file(filename);
    if(file.exists())
    {
        return true;
    }

    QDir dir(filename);
    if(dir.exists())
    {
        return true;
    }
    return false;
}

bool CFilePub::pathNoExist(QString filename)
{
    QFile file(filename);
    if(file.exists())
    {
        return false;
    }

    QDir dir(filename);
    if(dir.exists())
    {
        return false;
    }
    return true;
}


QString CFilePub::baseName(QString filename)
{
    QStringList list = filename.split(QRegExp(".*/"));
    if(list.length())
    {
        return list.at(0);
    }
    return CStringPub::emptyString();
}

QString CFilePub::dirName(QString filename)
{
    QStringList list = filename.split(QRegExp("[^/]*$"));
    if(list.length())
    {
        return list.at(0);
    }
    return CStringPub::emptyString();
}

/**
 * @brief CFilePub::createFileEmptyNoExistAndVar
 * @param m_Var
 * @param filename
 * @return
 * @desp 文件不存在则创建，并且置变量m_Var
 * @desp 支持多个文件处理，指filename包含;号
 */
bool CFilePub::createFileEmptyNoExistAndVar(QString &m_Var,QString filename)
{
    m_Var = filename;
    bool result = false;
    if(filename.contains(CSignPub::signFenHao()))
    {
        QStringList list = filename.split(CSignPub::signFenHao());
        foreach (QString item, list) {
            result |= createFileEmptyNoExist(item);
        }
    }
    else
    {
        return createFileEmptyNoExist(filename);
    }

    return result;
}
bool CFilePub::createFileEmptyNoExist(QString filename)
{
    if(fileExist(filename))
    {
        return true;
    }
    bool ok =  createDirNoExist(dirName(filename));
    if(CExpressPub::isFalse(ok))
    {
        return false;
    }
    ////////debugApp() << "create dirName          :" << dirName(filename);
    ////////debugApp() << "writeFileOnlly filename :" << filename;

    writeFileOnlly(filename, CStringPub::emptyString());
    return ok;
}

bool CFilePub::createFileContentNoExist(QString filename, QString content)
{
    if(fileExist(filename))
    {
        return true;
    }
    bool ok =  createDirNoExist(dirName(filename));
    if(CExpressPub::isFalse(ok))
    {
        return false;
    }
//    ////////debugApp() << "create dirName          :" << dirName(filename);
//    ////////debugApp() << "writeFileOnlly filename :" << filename;

    writeFileOnlly(filename, content);
    return ok;
}


bool CFilePub::createDirExt(QString dirname)
{
    QDir dir;
    bool ok = dir.mkpath(dirname);//mkpath创建多级目录, mkdir创建一级目录
    return ok;
}

bool CFilePub::createDirNoExist(QString dirname)
{
    if(CExpressPub::isZero(CStringPub::strSimLen(dirname)))
    {
        return false;
    }
    return createDirExt(dirname);
}
/**
 * @brief CFilePub::readFileAllFilterEmptyUniqueMulti
 * @param filename
 * @return
 * @desp 支持多文件读取，指filename中包含;号
 */
QStringList CFilePub::readFileAllFilterEmptyUniqueMulti(QString filename)
{
    QStringList result = CStringPub::emptyStringList();
    if(filename.contains(CSignPub::signFenHao()))
    {
        QStringList list = filename.split(CSignPub::signFenHao());
        foreach (QString item, list) {
            result.append(readFileAllFilterEmptyUnique(item));
        }
    }
    else
    {
        result.append(readFileAllFilterEmptyUnique(filename));
    }

    return result;
}

QStringList CFilePub::readFileAllFilterEmptyUnique(QString filename)
{
    return CStringPub::stringSplitbyNewLineFilterEmptyUnique(CFilePub::readFileAll(filename));
}

QStringList CFilePub::readFileAllFilterEmptyUniqueSort(QString filename)
{
    return CStringPub::stringSplitbyNewLineFilterEmptyUniqueSort(CFilePub::readFileAll(filename));
}

QStringList CFilePub::readFileAllFilterEmptyUniqueNoExistAndVar(QString &m_Var,QString filename)
{
    m_Var = filename;
    return CStringPub::stringSplitbyNewLineFilterEmptyUnique(CFilePub::readFileAll(filename));
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
    result = QString::fromUtf8(file.readAll());
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
    result = file.write(static_cast<const char *>(msg.toUtf8().data()));
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
    result = file.write(msg.toUtf8().data());
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
    result = file.write(msg.toUtf8().data());
    file.close();

    return msg;
}

QString CFilePub::writeFileWOnly(QString filename, QString msg)
{
    QString result("");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return result;
    }
    result = file.write(msg.toUtf8().data());
    file.close();

    return msg;
}

QString CFilePub::writeFileWOnly(QString filename, QStringList list)
{
    QString result("");
    QString msg = CStringPub::stringList2String(list, CSignPub::signEnterExt());
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return result;
    }
    result = file.write(msg.toUtf8().data());
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

/**
 * @brief CFilePub::deleteFileSameLineExt
 * @param filename
 * @param same
 * @return
 * @desp 支持多文件处理，指文件名中含有;号
 */
QString CFilePub::deleteFileSameLineExt(QString filename,QString same)
{
    if(filename.contains(CSignPub::signFenHao()))
    {
        QStringList list = filename.split(CSignPub::signFenHao());
        foreach (QString item, list) {
            deleteFileSameLine(item, same);
        }
    }
    else
    {
        deleteFileSameLine(filename, same);
    }

    return CStringPub::emptyString();
}

QString CFilePub::deleteFileSameLine(QString filename,QString same)
{
    QString result("");
    QFile file(filename);
    if(!file.exists())
    {
        CLogPub::logDefault("[deleteFileSameLine] no exist:" + filename);
        return result;
    }

    CLogPub::logDefault("[deleteFileSameLine] prepare ignore save:" + same);
    QString filecontent = readFileAll(filename);
    QStringList list = CStringPub::stringSplitbyNewLine(filecontent);
    foreach (QString item, list) {
        if(CStringPub::strSim(same) == CStringPub::strSim(item))
        {
            CLogPub::logDefault("[deleteFileSameLine] ignore save:" + same);
            continue;
        }
        result += item + CSignPub::signEnter();
    }

    CLogPub::logDefault("[deleteFileSameLine] filename:" + filename);
    writeFileOnlly(filename, result);

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
//    ////////debugApp() << "infolist:" << infolist.size();
    foreach (QFileInfo info, infolist) {
        QString temp = info.absolutePath() + QDir::separator() + info.fileName();
        files += QDir::toNativeSeparators(temp);
    }

    return files;
}

QStringList CFilePub::getFileAllRelateNames(QStringList nameFilters, const QString filePath)
{
    QStringList files;
    files.clear();
    QFileInfoList infolist = getAllFileList(nameFilters, filePath);
    //    ////////debugApp() << "infolist:" << infolist.size();
    foreach (QFileInfo info, infolist) {
        QString temp = info.absolutePath() + QDir::separator() + info.fileName();
        temp = CStringPub::toNativeSeparators(temp).replace(CStringPub::toNativeSeparators(filePath), CSignPub::signSpace());
        files += QDir::toNativeSeparators(temp);

//        ////////debugApp() << "temp:" << temp;
//        ////////debugApp() << "temp after:" << temp;
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

//    ////////debugApp() << "dirpath    :" << path;
//    ////////debugApp() << "file_list  :" << file_list.size();
//    ////////debugApp() << "folder_list:" << folder_list.size();

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
    ////////debugApp() << "Open Files:" << openfiles;
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
    ////////debugApp() << "Open Files:" << openfiles;
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
    ////////debugApp() << "Open Dir:" << openDirPath;
    recentlist.append(openDirPath);
    QStringList openfiles = CFilePub::getFileAllAbsoluteNames(nameFilters, openDirPath);
    return openfiles;
}

QString CFilePub::getCurrentPath()
{
    return QDir::currentPath() + QDir::separator();
}

QString CFilePub::getCurrentPath(QString filename)
{
    QString result = CStringPub::emptyString();

    if(filename.contains(CSignPub::signFenHao()))
    {
        QStringList list = filename.split(CSignPub::signFenHao());
        foreach (QString item, list) {
            result += QDir::currentPath() + QDir::separator() + item + CSignPub::signFenHao();
        }
        return result;
    }

    return QDir::currentPath() + QDir::separator() + filename;
}

QString CFilePub::getSeparator()
{
    return QDir::separator();
}

quint64 CFilePub::dirFileSize(const QString path)
{
    QDir dir(path);
    quint64 size = 0;
    //dir.entryInfoList(QDir::Files)返回文件信息
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files))
    {
        //计算文件大小
        size += fileInfo.size();
    }
    //dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)返回所有子目录，并进行过滤
    foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        //若存在子目录，则递归调用dirFileSize()函数
        size += dirFileSize(path + QDir::separator() + subDir);
    }
    return size;
}

qint64 CFilePub::fileSize(const QString path)
{
    QFileInfo fileInfo(path);
    qint64 size = 0;

    size += fileInfo.size();
    ////////debugApp() << "file size:" << size;
    return size;
}

QString CFilePub::parentDir(QString filepath)
{
    QFile file(filepath);
    //..必须添加/才行，即../
    QString dirPath = filepath + QDir::separator() + "../";
//    dirPath = QDir::toNativeSeparators(dirPath);
    dirPath = QDir::fromNativeSeparators(dirPath);
    return dirPath;
}
