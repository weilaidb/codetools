#ifndef DEBUGAPP_H
#define DEBUGAPP_H

#include <QDebug>

#ifdef QT_NO_DEBUG
//## release°æ±¾²»Êä³ö
//#DEFINES += QT_NO_DEBUG_OUTPUT
#define QT_NO_DEBUG_OUTPUT
#define debugApp qDebug
#define ENTERTIPS ;

#else
#define debugApp qDebug
#define ENTERTIPS ////debugApp() << __FUNCTION__ << ":" << __LINE__ ;

#endif

#endif // DEBUGAPP_H
