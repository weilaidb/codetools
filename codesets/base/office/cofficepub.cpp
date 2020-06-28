#include "cofficepub.h"
#include "cuipub.h"
#include "debugApp.h"
#include "cstringpub.h"
#include "signpub.h"

COfficePub::COfficePub()
{
    officeContent = nullptr;
    filepath_word_default = "D:\\test.docx";
}

COfficePub::COfficePub(QString text)
{
    officeContent = nullptr;
    filepath_word_default = "D:\\test.docx";
    findtext = text.trimmed();
}

COfficePub::~COfficePub()
{
    delete officeContent;
    delete this;
}

void COfficePub::openFile(QString filePath)
{
    int divnum = 10;
    if (filePath.isEmpty())
    {
        return;
    }
    if (officeContent)
    {
        closeFile();
    }
    if (filePath.endsWith(".docx") ||filePath.endsWith(".doc") || filePath.endsWith(".doc"))
    {
        officeContent=new QAxWidget ("Word.Document", nullptr);
        officeContent-> setGeometry (QRect (CUIPub::deskWidth()/divnum, CUIPub::deskWidth()/divnum
                                            , CUIPub::deskWidth()/1 - CUIPub::deskWidth()/divnum
                                            , CUIPub::deskHeigth()/1 -CUIPub::deskWidth()/divnum));
        officeContent->setControl (filePath);
        officeContent-> show ();
    }
    else if (filePath.endsWith(".xlsx") || filePath.endsWith(".xls") ||filePath.endsWith(".xlsm"))
    {
        officeContent=new QAxWidget ("Excel.WorkBook", nullptr);
        officeContent-> setGeometry (QRect (CUIPub::deskWidth()/divnum, CUIPub::deskWidth()/divnum
                                            , CUIPub::deskWidth()/1 - CUIPub::deskWidth()/divnum
                                            , CUIPub::deskHeigth()/1 -CUIPub::deskWidth()/divnum));
        officeContent->setControl (filePath);
        officeContent->show ();
    }
    else if (filePath.endsWith(".ppt") || filePath.endsWith(".pptx") ||filePath.endsWith(".pptm"))
    {
        //"Powerpoint.Presentation"

        officeContent=new QAxWidget ("Powerpoint.Application",nullptr);
        //pptPresentation->setControl("{048EB43E-2059-422F-95E0-557DA96038AF}");
        //pptPresentation->setControl("{91493441-5A91-11CF-8700-00AA0060263B}");
        officeContent-> setGeometry (QRect (CUIPub::deskWidth()/divnum, CUIPub::deskWidth()/divnum
                                            , CUIPub::deskWidth()/1 - CUIPub::deskWidth()/divnum
                                            , CUIPub::deskHeigth()/1 -CUIPub::deskWidth()/divnum));
        QAxObject *presentations = officeContent->querySubObject( "Presentations" );
        presentations->dynamicCall("Open(QString)",filePath);

    }
    else if (filePath.endsWith(".txt") || filePath.endsWith(".xml"))
    {

        QFile sfile(filePath);
        if (sfile.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&sfile);
            //            qEdit->setText(in.readAll());
            sfile.close();
        }
    }
    else
    {
        return;
    }
    currentFilePath=filePath;
}

void COfficePub::closeFile(bool isSave /*=false*/)
{
    if (officeContent)
    {
        if (currentFilePath.endsWith(".ppt") || currentFilePath.endsWith(".pptx") ||currentFilePath.endsWith(".pptm"))
        {
            officeContent->dynamicCall("Quit(void)");
        }
        else if (currentFilePath.endsWith(".txt") || currentFilePath.endsWith(".xml"))
        {
            //            ui.textEdit->clear();
        }
        else
        {
            officeContent->dynamicCall("Close(bool)",true);
        }
    }
}

void COfficePub::Save()
{

}

void COfficePub::SaveAs( QString newFilePath )
{

}


void COfficePub::testWord()
{
    //新建一个word应用程序，并设置为可见
    QAxWidget *pWord = new QAxWidget("Word.Application", nullptr, Qt::MSWindowsOwnDC);
    pWord->setProperty("Visible", true);
    //获取所有的工作文档
    QAxObject *pDocuments = pWord->querySubObject("Documents");
    //以文件template.dot为模版新建一个文档
    pDocuments->dynamicCall("Add(QString)", QString::fromLocal8Bit("E:/template.dot"));
    //获取当前激活的文档
    QAxObject *pDocument = pWord->querySubObject("ActiveDocument");
    //获取文档中名字为code的标签
    QAxObject *pBookMarkCode = pDocument->querySubObject("Bookmarks(QVariant)", "code");
    //选中标签，将字符code插入到标签位置
    if(!pBookMarkCode->isNull()){
        pBookMarkCode->dynamicCall("Select(void)");
        pBookMarkCode->querySubObject("Range")->setProperty("Text", "texg");
    }

    //将文件另存为docbyqt.doc,关闭工作文档，退出应用程序
    pDocument->dynamicCall("SaveAs(const QString &)", QString("c:/docbyqt.doc"));
    pDocument->dynamicCall("Close(boolean)", false);
    pWord->dynamicCall("Quit()");
}


QString COfficePub::readWord(QString filepath)
{
    QString docx_text_info;
    if(filepath.trimmed().isEmpty())
    {
        filepath=(filepath_word_default);
    }
    QAxWidget *m_word = new QAxWidget("Word.Application");
    m_word->setProperty("Visible",false);
    QAxObject *m_document = m_word->querySubObject("Documents");
    QAxObject *m_docx = m_document->querySubObject("Open(const QString&)",filepath);
    QAxObject *m_pRange;
    m_pRange=m_docx->querySubObject("Range()");
    docx_text_info=m_pRange->property("Text").toString();
    delete m_pRange;
    debugApp()<<docx_text_info << endl;
    //m_docx->dynamicCall("SaveAs(const QString&)", filepath);
    //m_docx->dynamicCall("Save()");
    m_docx->dynamicCall("Close()");
    delete m_docx;
    m_document->dynamicCall("Close()");
    delete m_document;
    m_word->clear();
    delete m_word;

    return docx_text_info;
}

QString COfficePub::readWordFindText(QString filepath)
{
    QString docx_text_info;
    if(filepath.trimmed().isEmpty())
    {
        filepath=(filepath_word_default);
    }

    QAxWidget *m_word = new QAxWidget("Word.Application");
    m_word->setProperty("Visible",false);
    QAxObject *m_document = m_word->querySubObject("Documents");
    QAxObject *m_docx = m_document->querySubObject("Open(const QString&)",filepath);
    QAxObject *m_pRange;
    m_pRange=m_docx->querySubObject("Range()");
    docx_text_info=m_pRange->property("Text").toString();
    delete m_pRange;
    //    debugApp()<<docx_text_info << endl;
    //m_docx->dynamicCall("SaveAs(const QString&)", filepath);
    //m_docx->dynamicCall("Save()");
    m_docx->dynamicCall("Close()");
    delete m_docx;
    m_document->dynamicCall("Close()");
    delete m_document;
    m_word->clear();
    delete m_word;

    return CStringPub::stringSplitFindText(docx_text_info, SIGNENTERSHUICHE, SIGNENTER, findtext);
}

























