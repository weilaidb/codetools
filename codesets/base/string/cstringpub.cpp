#include "cstringpub.h"
#include "csignpub.h"
#include "debugApp.h"
#include <QStringList>
#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <QDir>
#include <QTime>


CStringPub::CStringPub()
{

}

QStringList CStringPub::toStringListOnly(QString single)
{
    QStringList list;
    list.append(single);
    return list;
}

QStringList CStringPub::toStringList(const QList<QByteArray> list)
{
    QStringList strings;
    foreach (const QByteArray &item, list) {
        if(item.trimmed().isEmpty())
        {
            continue;
        }
        strings.append(QString::fromUtf8(item)); // Assuming local 8-bit.
    }
    return strings;
}

QString CStringPub::stringList2String(const QStringList list, const char *pSign)
{
    QString result("");
    foreach (QString item, list) {
        result += item + pSign;
    }

    return result;
}

QString CStringPub::stringList2StringEnter(const QStringList list)
{
    QString result("");
    foreach (QString item, list) {
        result += item + SIGNENTER;
    }

    return result;
}

int CStringPub::stringListCount(const QStringList list)
{
    return list.count();
}


QStringList CStringPub::stringSplit(const QString str , const char sign)
{
    return  str.split(sign);
}

QStringList CStringPub::stringSplitbyNewLine(const QString str)
{
    const char sign = '\n';
    return  str.split(sign);
}

QStringList CStringPub::stringSplitbyNewLineFilterEmpty(const QString str)
{
    return stringSplitbyCharFilterEmpty(str, '\n');
}

QStringList CStringPub::stringSplitbySpaceFilterEmpty(const QString str)
{
    return stringSplitbyCharFilterEmpty(str, ' ');
}

QStringList CStringPub::stringSplitbyCharFilterEmpty(const QString str, const char sign)
{
    QStringList result;
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        result.append(item);
    }

    return result;
}

QStringList CStringPub::stringSplitbyCharFilterEmpty(const QString str, QString sign)
{
    QStringList result;
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        result.append(item);
    }

    return result;
}


QStringList CStringPub::stringSplitbyNewLineTrimEnd(const QString str)
{
    QStringList listresult = CStringPub::emptyStringList();
    QStringList listtemp = CStringPub::stringSplitbyNewLine(str);
    foreach (QString item, listtemp) {
        listresult.append(item.replace(QRegExp("\\s*$"), ""));
    }
    return listresult;
}

QStringList CStringPub::stringSplitbyNewLineTrimHeader(const QString str)
{
    QStringList listresult = CStringPub::emptyStringList();
    QStringList listtemp = CStringPub::stringSplitbyNewLine(str);
    foreach (QString item, listtemp) {
        listresult.append(item.replace(QRegExp("^\\s*"), ""));
    }
    return listresult;
}

QStringList CStringPub::stringSplitbyNewLineTrimAll(const QString str)
{
    QStringList listresult = CStringPub::emptyStringList();
    QStringList listtemp = CStringPub::stringSplitbyNewLine(str);
    foreach (QString item, listtemp) {
        listresult.append(item.simplified());
    }
    return listresult;
}

QStringList CStringPub::stringSplitbyNewLineTrimEnd(const QStringList list)
{
    QStringList listresult = CStringPub::emptyStringList();
    foreach (QString item, list) {
        listresult.append(item.replace(QRegExp("\\s*$"), ""));
    }
    return listresult;
}

QStringList CStringPub::stringSplitbyNewLineFilterEmptyUnique(const QString str)
{
    QStringList result;
    const char sign = '\n';
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        //去除\r 空格等
        result.append(CStringPub::strSim(item));
    }

    result = CStringPub::stringUnique(result);
    return result;
}

QStringList CStringPub::stringSplitbyNewLineFilterEmptyUniqueSort(const QString str)
{
    QStringList result;
    const char sign = '\n';
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        //去除\r 空格等
        result.append(CStringPub::strSim(item));
    }

    result = CStringPub::stringUniqueSort(result);
    return result;
}


QString CStringPub::stringSplitFindText(const QString str , const char sign,QString signadd, QString findtext)
{
    QString result("");
    QStringList list = stringSplit(str, sign);
    foreach (QString item, list) {
        if(!item.contains(findtext))
        {
            continue;
        }
        result += item + signadd;
    }
    return result;
}

void CStringPub::printStringList(QStringList &lists)
{
    debugApp() <<"lists count:" << lists.count();
    quint32 dwCnt = 0;
    foreach (QString item, lists) {
        debugApp() << "No:" << ++dwCnt << ", " << item;
    }

}


QStringList CStringPub::reverseStringList(QStringList &lists)
{
    QStringList newlist;
    QStringList::reverse_iterator iter = lists.rbegin();
    for(;iter != lists.rend();iter++)
    {
        newlist.append(*iter);
    }
    return newlist;
}



QStringList CStringPub::stringUnique(QStringList lists)
{
    lists.removeDuplicates();
    return lists;
}

void CStringPub::addStringUnique(QStringList &lists,QString str)
{
    lists.append(str);
    lists.removeDuplicates();
}

void CStringPub::addStringUniqueMax(QStringList &lists, QString str, int max)
{
    lists.append(str);
    lists.removeDuplicates();
    while(lists.count() > max)
    {
        lists.removeFirst();
    }
}
//反序输出
void CStringPub::addStringUniqueInverseMax(QStringList &lists, QString str, int max)
{
    lists.append(str);
    lists.removeDuplicates();
    while(lists.count() > max)
    {
        lists.removeFirst();
    }
    lists = reverseStringList(lists);
}

//插入首节点,删除多余尾节点
void CStringPub::addStringHeaderUniqueMax(QStringList &lists, QString str, int max)
{
    lists.insert(0, str);
    lists.removeDuplicates();
    while(lists.count() > max)
    {
        lists.removeLast();
    }
}



void CStringPub::addStringUniqueSortMax(QStringList &lists, QString str, int max)
{
    lists.append(str);
    lists.removeDuplicates();
    if(lists.count() > max)
    {
        lists.removeFirst();
    }
    lists.sort();
}


QStringList CStringPub::stringUniqueSort(QStringList lists)
{
    lists.sort();
    lists.removeDuplicates();
    return lists;
}

QStringList CStringPub::stringUniqueSortReverse(QStringList lists)
{
    QStringList reverse;
    reverse.clear();
    lists.sort();
    lists.removeDuplicates();

    QVector<QString> list = lists.toVector();
    QVectorIterator<QString> iterator(list);

    //从结尾开始逆向遍历
    while(iterator.hasPrevious()){
        reverse.append(iterator.previous());
    }

    return lists;
}

QString CStringPub::getOpenFileNamesFilter(QStringList filters, QString sign)
{
    QString result("");
    foreach (QString item, filters) {
        result += item + sign;
    }
    return result;
}


QStringList CStringPub::emptyStringList()
{
    QStringList list;
    list.clear();
    return list;
}

QStringList CStringPub::emptyStringListCount(int count)
{
    QStringList list;
    list.clear();
    int lp = 0;
    for(lp = 0; lp < count; lp++)
    {
        list.append("");
    }
    return list;
}

QString CStringPub::emptyString()
{
    return QString("");
}

QString CStringPub::stringRegExpBefore()
{
    return QString("(.*)");
}

QString CStringPub::stringRegExpAfter()
{
    return QString("\\1");
}


QString CStringPub::errorListLenthNg()
{
    return QString("error:列表长度不足");
}

QString CStringPub::errorRegExpInvalid()
{
    return QString("error:正则表达式异常，请认真检测");
}


QStringList CStringPub::actionNameList(QAction *action)
{
    QStringList autolist;
    autolist.append(action->iconText());
    ////debugApp() << "actionname:" << action->iconText();
    return autolist;
}


QStringList CStringPub::languageNameFilter()
{
    QStringList list;
    list << "*.c";
    list << "*.cpp";
    list << "*.cxx";
    list << "*.h";
    list << "*.hpp";
    list << "*.java";

    return list;
}

QStringList CStringPub::wordNameFilter()
{
    QStringList list;
    list << "*.doc";
    list << "*.docx";

    return list;
}


bool CStringPub::strSimLenFull(QString str)
{
    return (str.simplified().length() > 0);
}

bool CStringPub::strSimLenZero(QString str)
{
    return (str.simplified().length() == 0);
}

bool CStringPub::strSimLenBiggerThan(QString str, quint32 dwMax)
{
    return strSimLen(str) > dwMax;
}

unsigned int CStringPub::strSimLen(QString str)
{
    return (unsigned int)str.simplified().length();
}

QString CStringPub::strSim(QString str)
{
    return str.simplified();
}

QString CStringPub::stringSelfMenu()
{
    return STRING_SELF_MENU;
}

QString CStringPub::constStringDoc()
{
    return "doc";
}

QString CStringPub::constStringTestCase()
{
    return "TestCase";
}

QString CStringPub::constStringLeftXieHao()
{
    return "/";
}

void CStringPub::clearString(QString &str)
{
    str.clear();
}

void CStringPub::setString(QString &str, QString val)
{
    str = val;
}

QString CStringPub::getString(QString &str)
{
    return str;
}

void CStringPub::clearStringList(QStringList &list)
{
    list.clear();
}


QString CStringPub::stringFilterEmpty(const QString str)
{
    QString result;
    const char sign = '\n';
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        result.append(item + sign);
    }

    return result;
}


bool CStringPub::atStringList(QString str, QStringList list)
{
    foreach (QString item, list) {
        if(CStringPub::strSim(item) == CStringPub::strSim(str))
        {
            return true;
        }
    }

    return false;
}

bool CStringPub::inStringList(QString str, QStringList list, Qt::CaseSensitivity cs)
{
    foreach (QString item, list) {
        if(item.contains(str, cs))
        {
            return true;
        }
    }

    return false;
}

void CStringPub::printDateTime()
{
    printf("Date : %s\n", __DATE__);
    printf("Time : %s\n", __TIME__);
    printf("File : %s\n", __FILE__);
    printf("Line : %d\n", __LINE__);
}


QString CStringPub::getDateTime()
{
    return QString("%1-%2").arg(__DATE__).arg(__TIME__);
}

QString CStringPub::GetStrOfData(unsigned char *in, int len)
{
    int i = 0;
    QString s;
    char buf[4];

    for (i=0; i<len; i++)
    {
        snprintf(buf,sizeof(buf),"%02x", in[i]);
        s.append(buf);
    }

    return s;
}

QString CStringPub::hexToString(unsigned char *in, int len)
{
    int i = 0;
    unsigned char inChar,hi,lo;
    QString s;

    for (i=0; i<len; i++)
    {
        inChar = in[i];

        hi = (inChar & 0xF0) >> 4;
        if (hi > 9)
            hi = 'A' + (hi - 0x0A);
        else
            hi += 0x30;
        s.append(hi);

        lo = inChar & 0x0F;
        if (lo > 9)
            lo = 'A' + (lo - 0x0A);
        else
            lo += 0x30;
        s.append(lo);

        //        s.append(0x20);
    }

    return s;
}

QString CStringPub::hexToString(unsigned char *in)
{
    return hexToString(in,strlen((char *)in));
}

QString CStringPub::getCurrentExePath()
{
    //Qt 获取当前程序运行路径
    //获取程序当前运行目录
    QString fileName = QCoreApplication::applicationDirPath();
    return fileName;
}

QString CStringPub::getSeperator()
{
    return QDir::separator();
}


bool CStringPub::contain(QString str, QString reg)
{
    return str.contains(QRegExp(reg));
}

string CStringPub::getDataOfStr(BYTE *pMsg, WORD32 dwLen)
{
    string res("");
    WORD32 dwLp = 0;
    CHAR buf[4];
    for(dwLp = 0; dwLp < dwLen; dwLp++)
    {
        snprintf(buf, sizeof(buf),"%02x", pMsg[dwLp]);
        res += buf;
    }

    return res;
}

//support multikey by space in filter
QStringList CStringPub::SameListInclude(QString filter, QStringList list)
{
    QStringList relist;
    foreach (QString item, list) {
        if(CStringPub::strSim(item) == CStringPub::strSim(filter))
        {
            relist.append(item);
        }
    }
    return relist;
}

//support multikey by space in filter
QStringList CStringPub::filterFileListInclude(QString filter, QStringList list, Qt::CaseSensitivity cs)
{
    QStringList relist;
    foreach (QString item, list) {
        if(filterKeySpaceInclude(filter, item, cs)){
            relist.append(item);
        }
    }
    return relist;
}

//不包含字符串filter
QStringList CStringPub::filterFileListNoInclude(QString filter, QStringList list, Qt::CaseSensitivity cs)
{
    QStringList relist;
    foreach (QString item, list) {
        if(item.contains(filter, cs)){
            continue;
        }
        relist.append(item);
    }
    return relist;
}


bool CStringPub::filterKeySpaceInclude(QString keySpace, QString orgtext, Qt::CaseSensitivity cs)
{
    QStringList keyList = stringSplitbySpaceFilterEmpty(keySpace);
    quint16 wCount = 0;
    foreach (QString item, keyList) {
        if(orgtext.contains(item,cs))
        {
            wCount++;
        }
    }

//    debugApp() << "cs:"<<cs << ",wCount:"<<wCount << ",keyList size:" << keyList.size()<< ",keySpace:"<<keySpace << ",orgtext:" << orgtext;
    if(wCount == keyList.size())
    {
        return true;
    }
    return false;
}

QString CStringPub::toNativeSeparators(QString dir)
{
    return  QDir::toNativeSeparators(dir);
}
//BYTE数组转换成字符串显示
QString CStringPub::getStringOfData(unsigned char *pStr, unsigned int dwLen, int hexflag)
{
    QString result("");
    WORD32 dwLp =  0;
    char buf[4] = {0};
    for(dwLp = 0;dwLp < dwLen;dwLp++)
    {
        if(16 == hexflag)
        {
            snprintf(buf,sizeof(buf),"%02x",pStr[dwLp]);
        }
        else
        {
            snprintf(buf,sizeof(buf),"%02u ",pStr[dwLp]);
        }
        result.append(buf);
    }
    return result;
}

bool CStringPub::endWithExcel(QString filename)
{
    return filename.endsWith("xls") || filename.endsWith("xlsx");
}

int CStringPub::randomData()
{
    static quint32 dwLp = 0;
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000 + qrand() * dwLp++);
    return qrand();
}

quint8 CStringPub::randomData8()
{
    return  randomData() % 0xFF;    //产生0xFF以内的随机数
}

quint16 CStringPub::randomData16()
{
    return  randomData() % 0xFFFF;    //产生0xFFFF以内的随机数
}

quint32 CStringPub::randomData32()
{
    return  randomData() % 0xFFFF << 16 | randomData() % 0xFFFF;    //产生0xFFFFFFFF以内的随机数
}


QString CStringPub::scaleConvertPub(QString text, quint8 from, quint8 to)
{
    bool ok;
    qulonglong dec = text.toULongLong(&ok, from);
    if(16 == to)
    {
        text = QString::number(dec,to);
//        debugApp() << "text:" << text;
//        text = QString::number(dec,to).right(4); //裁剪字符串前面多余的f
    }
    else
    {
        text = QString::number(dec,to);
    }
    return text;
}

QString CStringPub::toUpper(QString text)
{
    return text.toUpper();
}

QString CStringPub::toLower(QString text)
{
    return text.toLower();
}

QString CStringPub::add0xDot(QString text)
{
    return "0x" + text + ",";
}

qulonglong CStringPub::strToHex(QString text)
{
    return text.toULongLong(nullptr, 16);
}

qulonglong CStringPub::strToDec(QString text)
{
    return text.toULongLong();
}


QString CStringPub::replaceReg(QString text, QString regexp, QString after)
{
    return text.replace(QRegExp(regexp), after);
}

QString CStringPub::replaceReg2Empty(QString text, QString regexp)
{
    return replaceReg(text, regexp, "");
}
QString CStringPub::replaceRegLRKuohao2Empty(QString text)
{
    return replaceReg(text, "[【[].*[]】]", "");
}

int CStringPub::removeAll(QStringList &list, QString str)
{
    return list.removeAll(str);
}

QString CStringPub::getHttpStr(QString prefix,QString text)
{
    QByteArray byteArrayPercentEncoded = text.toLocal8Bit().toPercentEncoding();
    return  prefix + byteArrayPercentEncoded;
}

void CStringPub::deleteListItem(QStringList &list, QString str)
{
    list.removeAll(str);
}

QStringList CStringPub::stringFilterFirstEnd(const QStringList list, QString leftSign, QString rightSign)
{
    QStringList resList = emptyStringList();
    foreach (QString item, list) {
        item = item.simplified();
        if(item.length() == 0 )
        {
            continue;
        }
        if(item.at(0) == leftSign || item.at(item.length() - 1) == rightSign)
        {
            continue;
        }
        resList.append(item);
    }

    return resList;
}

//判断字符是数字
bool CStringPub::regExpIsDigtals(QString str)
{
    return str.contains(QRegExp("^\\d+$"));
}
//冒号后是数字
bool CStringPub::regExpMaoHaoAfterDigtals(QString str)
{
    return str.contains(QRegExp("^.*:\\d+.*$"));
}

void CStringPub::appendStringEnter(QString &result, QString str)
{
    result.append(str).append("\n");
}

QString CStringPub::getSystemTimePub(QString fmt)
{
    return  QTime::currentTime().toString(fmt);
}

QString CStringPub::getSystemTime()
{
    return getSystemTimePub("hh:mm:ss");
}

QString CStringPub::getSystemTime2()
{
    return getSystemTimePub("hh_mm_ss");
}

QString CStringPub::getSystemDatePub(QString fmt)
{
    return QDateTime::currentDateTime().toString(fmt);
}

QString CStringPub::getSystemDate()
{
    return getSystemDatePub("yyyy-MM-dd hh:mm:ss");
}

QString CStringPub::getSystemDate2()
{
    return getSystemDatePub("yyyy-MM-dd hh_mm_ss");
}

void CStringPub::appendString(QString &result, QString str)
{
    result.append(str);
}
