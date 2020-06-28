#ifndef COFFICEPUB_H
#define COFFICEPUB_H

#include <QString>
#include <QWidget>
#include <QAxObject>
#include <QAxWidget>
#include <QTextStream>
#include <QFile>
#include <QTextEdit>

class COfficePub
{
public:
    COfficePub();
    ~COfficePub();
public:
    //打开文件  ;*.doc;*.docx;*.docm;*.xls;*.xlsx;*.xlsm;*.xlsb,*.ppt;*.pptx;*.pptm;*.txt;*.xml;
    void openFile(QString filePath);
    //关闭 是否需要保存 默认不保存
    void closeFile(bool isSave=false);
    //保存
    void Save();
    //另存为。。
    void SaveAs(QString newFilePath);


    //word
    void testWord();
    QString readWord(QString filepath);

private:
    //文档打开控件
    QAxWidget* officeContent;
    //当前打开文件的路径
    QString currentFilePath;

};

#endif // COFFICEPUB_H
