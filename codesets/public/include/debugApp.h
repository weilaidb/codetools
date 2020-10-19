#ifndef DEBUGAPP_H
#define DEBUGAPP_H

#include <QDebug>

#ifdef QT_NO_DEBUG
//## release版本不输出
//#DEFINES += QT_NO_DEBUG_OUTPUT
#define QT_NO_DEBUG_OUTPUT

#else

#endif
#define debugApp qDebug
#define ENTERTIPS debugApp() << __FUNCTION__ << ":" << __LINE__ ;

#endif // DEBUGAPP_H
