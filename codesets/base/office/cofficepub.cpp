#include "cofficepub.h"
#include "cuipub.h"

COfficePub::COfficePub()
{
    officeContent = nullptr;
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

