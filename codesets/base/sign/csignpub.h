#ifndef CSIGNPUB_H
#define CSIGNPUB_H

#include <QString>


#define SIGNENTER           "\n"
#define SIGNENTERLR         "\r\n"
#define SIGN_RE_SPACE         "\\s+"
#define SIGNSPACE         "  "
#define SIGNDOUBLEFENHAO  ";;"
#define SIGNDOUHAO  ","
#define SIGNFENHAO  ";"
#define SIGNDOT  "."
#define SIGNFENHAOC  ';'


#define SIGNENTERS '\n'
#define SIGNENTERSHUICHE '\r'
#define SIGLEFTXIELINE '/'

#define FILTERWORD     (";*.doc;*.docx;")
#define FILTERDOCUMENT (";*.doc;*.docx;*.docm;*.xls;*.xlsx;*.xlsm;*.xlsb,*.ppt;*.pptx;*.pptm;*.txt;*.xml;;*.*")

#define STRINGEMPTY     ("")
#define EMPTYSTRING     STRINGEMPTY

#define STRING_PLEASE_SELECT_DIR     ("请选择文件夹")
#define STRING_PLEASE_SELECT_FILE     ("请选择文件")
#define STRING_RES_FIND_FILES_EMPTY    ("未找到文件")
#define STRING_INPUT_FIND_KEY_EMPTY    ("输入关键字为空")

#define STRING_TIPS_FILE_NO_EXIST    ("文件不存在")
#define STRING_TIPS_DIR_NO_SUPPORT    ("文件夹不支持")


class CSignPub
{
public:
    CSignPub();

    static QString signEnter();
    static QString signDot();
    static const char *signEnterExt();
    static char signEnterS();
    static QString signEnterNL();
    static QString signRESpace();
    static char signLXie();
    static QString signFenHao();
    static char signFenHaoC();


};

#endif // CSIGNPUB_H
