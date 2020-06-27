QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AStyle_3_1_windows/AStyle/src/ASBeautifier.cpp \
    AStyle_3_1_windows/AStyle/src/ASEnhancer.cpp \
    AStyle_3_1_windows/AStyle/src/ASFormatter.cpp \
    AStyle_3_1_windows/AStyle/src/ASLocalizer.cpp \
    AStyle_3_1_windows/AStyle/src/ASResource.cpp \
    AStyle_3_1_windows/AStyle/src/astyle_main.cpp \
    base/source/cfilepub.cpp \
    base/source/cprintpub.cpp \
    base/source/cstringpub.cpp \
    base/source/cuipub.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AStyle_3_1_windows/AStyle/src/ASLocalizer.h \
    AStyle_3_1_windows/AStyle/src/astyle.h \
    AStyle_3_1_windows/AStyle/src/astyle_main.h \
    base/include/cfilepub.h \
    base/include/cprintpub.h \
    base/include/cstringpub.h \
    base/include/cuipub.h \
    mainwindow.h \
    public/include/basepub.h \
    public/include/debugApp.h \
    public/include/expresspub.h \
    public/include/filepub.h \
    public/include/signpub.h \
    version.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += AStyle_3_1_windows/AStyle/src \
    public/include/ \
    base/include/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/app.qrc

RC_FILE = \
    images/myapp.rc




DISTFILES += \
    images/myapp.rc
