#ifndef CVECPUB_H
#define CVECPUB_H

#include <QLabel>
#include <QPushButton>
#include <QVector>



class CVecPub
{
public:
    CVecPub();

    static void insertVec(QVector<QLabel *> &vec, QLabel *label);
    static void insertVec(QVector<QPushButton *> &vec, QPushButton *button);
};

#endif // CVECPUB_H
