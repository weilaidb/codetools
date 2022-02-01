/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *le_Host;
    QLabel *label_2;
    QLineEdit *le_User;
    QLabel *label_3;
    QLineEdit *le_Passwd;
    QPushButton *pb_Link;
    QPushButton *pb_close;
    QTextEdit *te_Msg;
    QPushButton *pb_Send;
    QLineEdit *le_SendText;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(713, 483);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        le_Host = new QLineEdit(centralWidget);
        le_Host->setObjectName(QStringLiteral("le_Host"));

        gridLayout->addWidget(le_Host, 0, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        le_User = new QLineEdit(centralWidget);
        le_User->setObjectName(QStringLiteral("le_User"));

        gridLayout->addWidget(le_User, 0, 3, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        le_Passwd = new QLineEdit(centralWidget);
        le_Passwd->setObjectName(QStringLiteral("le_Passwd"));

        gridLayout->addWidget(le_Passwd, 0, 5, 1, 1);

        pb_Link = new QPushButton(centralWidget);
        pb_Link->setObjectName(QStringLiteral("pb_Link"));

        gridLayout->addWidget(pb_Link, 0, 6, 1, 1);

        pb_close = new QPushButton(centralWidget);
        pb_close->setObjectName(QStringLiteral("pb_close"));

        gridLayout->addWidget(pb_close, 0, 7, 1, 1);

        te_Msg = new QTextEdit(centralWidget);
        te_Msg->setObjectName(QStringLiteral("te_Msg"));

        gridLayout->addWidget(te_Msg, 1, 0, 1, 8);

        pb_Send = new QPushButton(centralWidget);
        pb_Send->setObjectName(QStringLiteral("pb_Send"));

        gridLayout->addWidget(pb_Send, 2, 7, 1, 1);

        le_SendText = new QLineEdit(centralWidget);
        le_SendText->setObjectName(QStringLiteral("le_SendText"));

        gridLayout->addWidget(le_SendText, 2, 0, 1, 7);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Telnet\345\256\242\346\210\267\347\253\257", 0));
        label->setText(QApplication::translate("MainWindow", "IP\345\234\260\345\235\200\357\274\232", 0));
        label_2->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        label_3->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", 0));
        pb_Link->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", 0));
        pb_close->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200", 0));
        pb_Send->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
