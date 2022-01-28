#ifndef CVECPUB_H
#define CVECPUB_H

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVector>



class CVecPub
{
public:
    CVecPub();

    static void insertVec(QVector<QLabel *> &vec, QLabel *label);
    static void insertVec(QVector<QPushButton *> &vec, QPushButton *button);
    static void insertVec(QVector<QTextEdit *> &vec, QTextEdit *textedit);
    static void deleteVec(QVector<QLabel *> &vec);
    static void deleteVec(QVector<QPushButton *> &vec);
    static void deleteVec(QVector<QTextEdit *> &vec);
};

#endif // CVECPUB_H
