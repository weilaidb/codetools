#include "formcenter.h"
#include "ui_formcenter.h"

FormCenter::FormCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCenter)
{
    ui->setupUi(this);

}

FormCenter::~FormCenter()
{
    delete ui;
}

void FormCenter::initButtonSets()
{
    QObject::connect(ui->pushButton_tryagain, SIGNAL(clicked()), this, SLOT(proc_pushButton_tryagain()));
}


void FormCenter::proc_pushButton_tryagain()
{
    proc_action_TryAgain();
}

void FormCenter::proc_action_TryAgain()
{
//    //编辑配置文件模式
//    if(CUIPub::isCheckedQAction(ui->action_EditCfgFile)
//            || CExpressPub::isEmpty(m_EditConfig))
//    {
//        return;
//    }

//    setWindowTitle(QString("生成代码【%1】").arg(m_EditConfig));
//    proc_action_gen_pub(m_EditConfig, EUM_CLASSTYPE::COMMON_OPERATIONS);

}
