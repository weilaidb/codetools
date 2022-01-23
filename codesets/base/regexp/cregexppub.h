#ifndef CREGEXPPUB_H
#define CREGEXPPUB_H


#include <QRegExp>
#include <QRegularExpression>
#include "basetypepub.h"
#include "cfilepub.h"

#define STR_MODE_NONE                        ("MODE_NONE")
#define STR_MODE_ALALLINE_EXECMULTI          ("MODE_ALALLINE_EXECMULTI")    //左侧所有行内容，进行多次处理（右侧）
#define STR_MODE_SINGLELINE_EXECMULTI        ("MODE_SINGLELINE_EXECMULTI")  //左侧一行内容，进行多次处理（右侧）
#define STR_MODE_SINGLELINE_EXECSINGLE       ("MODE_SINGLELINE_EXECSINGLE")  //左侧一行内容，进行一次处理（右侧）
#define STR_MODE_MUL2ONE        ("MODE_MUL2ONE")

/**
  **
  ** 自定义特殊符
  **/
#define SIGN_CUSTOM_NL        ("$NL")
#define SIGN_CUSTOM_TB        ("$TB")
#define SIGN_CUSTOM_SP        ("$SP")
#define SIGN_CUSTOM_DATE      ("$DATE")
#define SIGN_CUSTOM_DATEX     ("$DATEX")  //日期以_号连接
#define SIGN_CUSTOM_DATEY     ("$DATEY")  //日期以_号连接
#define SIGN_CUSTOM_H2D       ("$H2D")    //hexadecimal to decimal
#define SIGN_CUSTOM_D2H       ("$D2H")    //decimal to hexadecimal
#define SIGN_CUSTOM_H2B       ("$H2B")    //hexadecimal to binary
#define SIGN_CUSTOM_B2H       ("$B2H")    //binary to hexadecimal
#define SIGN_CUSTOM_D2B       ("$D2B")    //decimal to binary
#define SIGN_CUSTOM_B2D       ("$B2D")    //binary to decimal
#define SIGN_CUSTOM_UPP       ("$UP")     //转大写
#define SIGN_CUSTOM_LOW       ("$LO")     //转小写
#define SIGN_CUSTOM_0XDOT     ("$0XDOT")  //报文添加0x和逗号
#define SIGN_CUSTOM_FORFXIE   ("$FORFX")  //生成递增的反斜线 \1\2\3...
#define SIGN_CUSTOM_FORW      ("$FORW")   //生成相同个数的内容(\w{2})(\w{2})...(\w{2})(.*)
#define SIGN_CUSTOM_BIT       ("$BIT")    //取某个数据的某些bit位，参数为:选择数，起始bit位(从0开始)，长度

#define LASTWITH(ARR)  ARR[ARR.size() - 1]
#define MIDWITH(ARR, LP)  ARR[LP]



/**是否包含要转换的符号(嵌套) */
#define CHECK_INCLUDE(text,express) \
    while(\
    0\
    ||text.contains (SIGN_CUSTOM_NL      )\
    ||text.contains (SIGN_CUSTOM_TB      )\
    ||text.contains (SIGN_CUSTOM_SP      )\
    ||text.contains (SIGN_CUSTOM_DATE    )\
    ||text.contains (SIGN_CUSTOM_DATEX   )\
    ||text.contains (SIGN_CUSTOM_DATEY   )\
    ||text.contains (SIGN_CUSTOM_H2D     )\
    ||text.contains (SIGN_CUSTOM_D2H     )\
    ||text.contains (SIGN_CUSTOM_H2B     )\
    ||text.contains (SIGN_CUSTOM_B2H     )\
    ||text.contains (SIGN_CUSTOM_D2B     )\
    ||text.contains (SIGN_CUSTOM_B2D     )\
    ||text.contains (SIGN_CUSTOM_UPP     )\
    ||text.contains (SIGN_CUSTOM_LOW     )\
    ||text.contains (SIGN_CUSTOM_0XDOT   )\
    ||text.contains (SIGN_CUSTOM_FORFXIE )\
    ||text.contains (SIGN_CUSTOM_FORW    )\
    ||text.contains (SIGN_CUSTOM_BIT     )\
)\
{\
    (express);\
}



typedef struct T_handlerRegExpParas{
    QString text;
    QStringList regbefore;
    QStringList regafter;
    QString mode;
    quint8 ucMultLineMultiProcMode; /* A/B模式 多行多处理 ,见 EUM_MODE_MULTILINE_MULTIPROC */
}T_handlerRegExpParas, *P_handlerRegExpParas;


typedef QString (*handlerRegExp)(T_handlerRegExpParas &tHandlerParas);
typedef QString (*handlerTip)(QString configfilename, quint32 dwClasstype, int filetype);
typedef QString (*handlerPost)(QString text);


typedef struct T_GenCode{
    WORD32 dwClasstype;    /* 类型 */
    QString filename ;    /* 文件名称 */
    handlerRegExp m_handler ;    /* 回调函数 */
    handlerTip    m_tip ;    /* 帮忙，提示 */
    handlerPost   m_handler_post ;    /* 回调后函数 */
}T_GenCode, *P_GenCode;


enum EUM_CLASSTYPE{
    CONSTRUCTOR,
    DESTRUCTOR,
    GETTER,
    SETTER,
    GETTER_AND_SETTER,
    EQUALITY_OPERATOR,
    RELATIONAL_OPERATOR,
    STREAM_OUTPUT_OPERATER,
    OVEERRIDE_FUNCTIONS,
    IMPLEMENT_FUNCTIONS,
    GENERATE_DEFINATION,
    COMMON_OPERATIONS, //公共使用
    EDIT_CFGFILE_OPERATIONS, //编辑配置
};

/* A/B模式 多行多处理 */
enum EUM_MODE_MULTILINE_MULTIPROC{
    A_MODE_MULTILINE_MULTIPROC,
    B_MODE_MULTILINE_MULTIPROC,
};


typedef struct T_SignPub{
    const char *m_funname; //函数名
    const char *m_filterregexp; //过滤正则表达式
    //    const char *m_funname; //函数名
}T_SignPub, *P_SignPub;

//参数列表
typedef struct T_RegExpParas{
    QString classconfig;
    quint32 dwClasstype;
    QString text;
    quint8 ucMultLineMultiProcMode; /* A/B模式 多行多处理 ,见 EUM_MODE_MULTILINE_MULTIPROC */
}T_RegExpParas, *P_RegExpParas;




class CRegExpPub
{
public:
    enum EUM_FILETYPE{
        FILE_TIPS,
        FILE_BEFORE,
        FILE_AFTER,
    };

    enum EUM_MODE{
        MODE_NONE,
        MODE_ALLLINE_EXECMULTI,
        MODE_SINGLELINE_EXECMULTI,
        MODE_SINGLELINE_EXECSINGLE,
        MODE_MUL2ONE,
    };


    CRegExpPub();
    //set
    static QString setRegExpByFile(QString filename, QString content);
    //get
    static QString getFileSuffix(QString filename);
    static QString getRenameFile(QString filename);
    static QString getRegExpFileNameBefore(QString filename);
    static QString getRegExpFileNameAfter(QString filename);
    static QString getRegExpFileNameTips(QString filename);
    static QString getRegExpFileNamePub(QString filename, int filetype);
    static QString getRegExpByFile(QString filename, QString content);
    static QStringList getRegExpsByFile(QString filename,QString content);
    static QString getFileNameByClassType(quint32 dwClasstype);
    static QString procTextByRegExpList(T_RegExpParas &tPara);
    static QString checkRegExpFile(QString classconfig, quint32 dwClasstype
                                   , QStringList &regexpsbef
                                   , QStringList &regexpsaft
                                   , QStringList &regexpstip
                                   , QString &regexpmode);
    static QString getFileNameByClassCfgType(QString classconfig, quint32 dwClasstype);
    static QString replaceSignsPub(QString text);
    static QString replaceSignsItemPub(QString text);
    static QString replaceSignsItemFuncPub(QString dealText, P_SignPub temp);
    static QString replaceSignsItemTestPub(QString text);
    static QString replaceSeqPub(QString text, int iStartSeq, int dwCount, QRegularExpressionMatch match);
    static QString replaceSeqMultiPub(QString text, QString regafter, int iStartSeq, int iCount, QRegularExpressionMatch match, int &index);
    static bool handlerRegExp_PubCheck(QString text, QStringList regbefore, QStringList regafter, QString mode);
    static QString handlerRegExp_Pub(T_handlerRegExpParas &tHandlerRegExpPara);
    static QString handlerRegExp_Special(QString text, QStringList regbefore, QStringList regafter, QString mode);
    static QString handlerRegExp_Pub_Single(QString text, QStringList regbefore, QStringList regafter, QString mode);
    static QString handlerRegExp_Pub_Single(QString text, QString regbefore, QString regafter, QString mode);
    static QString handlerRegExp_Pub_MultiLine(QString text, QString regbefore, QString regafter, QString mode, QString &error, quint8 ucModeExt);
    static QString procRegExpLineLack(QStringList strlisttmp, QStringList &reg2list, QStringList regcmplist);
    static QString handlerTip_Getter(QString configfilename, quint32 dwClasstype, int filetype);
    static QString handlerTip(QString classconfig, quint32 dwClasstype, int filetype);
    static void handlerTipSave(QString classconfig, quint32 dwClasstype, QString content, int filetype);
    static QString handlerPost_Pub(QString text);
    //    static QString handlerRegExp_Setter(QString text,QStringList regbefore, QStringList regafter);
    //    static QString handlerTip_Setter();

    static const QString getConfigBefore();
    static const QString getConfigBase();

private:
    static const QString dirbase;
    static const QString dirbefore;
    static const QString dirafter;
    static const QString dirtips;
};





#endif // CREGEXPPUB_H
