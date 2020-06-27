#include "cuipub.h"

CUIPub::CUIPub()
{

}



void CUIPub::Var2Map(QSettings &sets, QString envkey, QMap<QString, QStringList> &outmap)
{
    QMap<QString, QVariant> maptmp = sets.value(envkey).toMap();

    //map_showcmd
    QMapIterator<QString, QVariant> i(maptmp);
    while (i.hasNext()) {
        i.next();
        QString key = i.key();
        QVariant val = i.value();
        outmap.insert(key, val.toStringList());
    }
}

QMap<QString, QVariant> CUIPub::Map2Var(QMap<QString, QStringList> &inmap)
{
    QMap<QString, QVariant> maptmp;
    maptmp.clear();
    QMapIterator<QString, QStringList> i(inmap);
    while (i.hasNext()) {
        i.next();
        QString key = i.key();
        QVariant val = i.value();
        maptmp.insert(key, val);
    }
    return maptmp;
}





/**
 * @brief CUIPub::ReadHistorySettings
 */
void CUIPub::ReadHistorySettings(QString &organization,
                                 const QString &application)
{
    QSettings m_settings(organization, application);
//    ui->comboBox->addItems(m_settings.value("ComBoxIPList").toStringList());
//    ComBoxIPList = m_settings.value("ComBoxIPList").toStringList();
//    ui->comboBox->setEditText(m_settings.value("curkey").toString());
//    curmodeldir = m_settings.value("curmodeldir").toString();
//    //    show_cmdlist.clear();
//    //    show_cmdlist = m_settings.value("listWidget_cmdlist").toStringList();

//    Var2Map(m_settings, "map_showcmd", map_showcmd);
//    Var2Map(m_settings, "map_commonuselist", map_commonuselist);

//    //    mapIpAndContent
//    //    ui->lineEdit->setText(m_settings.value("LineEditIP").toString());
//    ui->checkBox_autosend->setChecked(m_settings.value("checkBox_autosend").toBool());
//    ui->checkBox_treeopen->setChecked(m_settings.value("checkBox_treeopen").toBool());
//    ui->checkBox_fileautoload->setChecked(m_settings.value("checkBox_fileautoload").toBool());
//    ui->checkBox_tree->setChecked(m_settings.value("checkBox_tree").toBool());
//    ui->checkBox_dict_realtime->setChecked(m_settings.value("checkBox_dict_realtime").toBool());
//    ui->checkBox_openfirstitem->setChecked(m_settings.value("checkBox_openfirstitem").toBool());
//    ui->checkBox_watchhttp->setChecked(m_settings.value("checkBox_watchhttp").toBool());
//    this->restoreGeometry(m_settings.value("Cmdserver").toByteArray());

}

/**
 * @brief CUIPub::WriteCurrentSettings
 */
void CUIPub::WriteCurrentSettings(QString &organization,
                                  const QString &application)
{
    QSettings m_settings(organization, application);
//    m_settings.setValue("ComBoxIPList",ComBoxIPList);
//    m_settings.setValue("curkey", ui->comboBox->currentText());
//    m_settings.setValue("curmodeldir", curmodeldir);
//    //    show_cmdlist.clear();
//    //    int count = ui->listWidget_cmdlist->count();
//    //    int loop = 0;
//    //    for(loop = 0; loop < count;loop++)
//    //    {
//    //        cmdlist << ui->listWidget_cmdlist->item(loop)->text();
//    //    }
//    m_settings.setValue("listWidget_cmdlist",show_cmdlist);

//    m_settings.setValue("map_showcmd", Map2Var(map_showcmd));
//    m_settings.setValue("map_commonuselist", Map2Var(map_commonuselist));


//    m_settings.setValue("checkBox_autosend",ui->checkBox_autosend->isChecked());
//    m_settings.setValue("checkBox_treeopen",ui->checkBox_treeopen->isChecked());
//    m_settings.setValue("checkBox_fileautoload",ui->checkBox_fileautoload->isChecked());
//    m_settings.setValue("checkBox_tree",ui->checkBox_tree->isChecked());
//    m_settings.setValue("checkBox_dict_realtime",ui->checkBox_dict_realtime->isChecked());
//    m_settings.setValue("checkBox_openfirstitem",ui->checkBox_openfirstitem->isChecked());
//    m_settings.setValue("checkBox_watchhttp",ui->checkBox_watchhttp->isChecked());


//    m_settings.setValue("Cmdserver", this->saveGeometry());
}

void CUIPub::clearMenu(QMenu *pMenu)
{
    //先删除当前节点
    QList<QAction*> listActions = pMenu->actions();
    foreach (QAction *action, listActions) {
        delete action;
    }
    pMenu->clear();
}

void CUIPub::addMenu(QMenu *pMenu, QString item)
{
    QAction *pAction = new QAction(item);
    pMenu->addAction(pAction);
}
