#ifndef DEBUGAPP_H
#define DEBUGAPP_H

#include <QDebug>

#define debugApp qDebug
#define ENTERTIPS debugApp() << __FUNCTION__ << ":" << __LINE__ ;

#endif // DEBUGAPP_H
