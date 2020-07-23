#include "calgorithmpub.h"
#include "basetypepub.h"
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <cstringpub.h>

CAlgorithmPub::CAlgorithmPub()
{

}

QString CAlgorithmPub::getMd5SumOfFile(QString filePath)
{

    QFile localFile(filePath);

    if (!localFile.open(QFile::ReadOnly))
    {
        qDebug() << "file open error.";
        return 0;
    }

    QCryptographicHash ch(QCryptographicHash::Md5);

    quint64 totalBytes = 0;
    quint64 bytesWritten = 0;
    quint64 bytesToWrite = 0;
    quint64 loadSize = 1024 * 4;
    QByteArray buf;

    totalBytes = localFile.size();
    bytesToWrite = totalBytes;

    while (1)
    {
        if(bytesToWrite > 0)
        {
            buf = localFile.read(qMin(bytesToWrite, loadSize));
            ch.addData(buf);
            bytesWritten += buf.length();
            bytesToWrite -= buf.length();
            buf.resize(0);
        }
        else
        {
            break;
        }

        if(bytesWritten == totalBytes)
        {
            break;
        }
    }

    localFile.close();
    QByteArray md5 = ch.result();
    // 转化
    char *md5buf = md5.data();//只是一个指针
    int md5len = md5.size();//buf的长度

    QString result = "MD5:" +  CStringPub::hexToString((BYTE *)md5buf, md5len);

    return result;
}
