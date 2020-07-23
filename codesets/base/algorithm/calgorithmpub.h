#ifndef CALGORITHMPUB_H
#define CALGORITHMPUB_H

#include <QString>

class CAlgorithmPub
{
public:
    CAlgorithmPub();
    static QString getMd5SumOfFile(QString filename);
};

#endif // CALGORITHMPUB_H
