QT       += core gui
QT       += sql
QT       += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#添加外部的引用头文件和库文件
INCLUDEPATH += AStyle_3_1_windows/AStyle/src \
    public/include/ \
    base/include/ \
    base/msgtips/ \
    base/mysql/ \
    base/office/ \
    base/dialog/ \
    base/thread/ \
    base/regexp/ \
    base/net/zeromq/ \
    libs/libzmq-v141-4_3_2 \
    cppbase/string/ \
    cppbase/include/ \

#$$PWD指当前路径， -l指定的文件去掉 .lib 以及 lib替换为l
LIBS += -L$$PWD/libs/libzmq-v141-4_3_2  -lzmq-v141-mt-4_3_2


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
    base/dialog/cdialogpub.cpp \
    base/msgtips/cmsgtips.cpp \
    base/mysql/csqlpub.cpp \
    base/net/zeromq/cnetpub.cpp \
    base/office/cofficepub.cpp \
    base/regexp/regexppub.cpp \
    base/source/cfilepub.cpp \
    base/source/cprintpub.cpp \
    base/source/cstringpub.cpp \
    base/source/cuipub.cpp \
    base/thread/cnetthreadpub.cpp \
    base/thread/cthreadpub.cpp \
    cppbase/string/cstringpubcpp.cpp \
    cppbase/string/testcase/cstringpubcpp_main.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AStyle_3_1_windows/AStyle/src/ASLocalizer.h \
    AStyle_3_1_windows/AStyle/src/astyle.h \
    AStyle_3_1_windows/AStyle/src/astyle_main.h \
    base/dialog/cdialogpub.h \
    base/include/cfilepub.h \
    base/include/cprintpub.h \
    base/include/cstringpub.h \
    base/include/cuipub.h \
    base/msgtips/cmsgtips.h \
    base/mysql/csqlpub.h \
    base/net/zeromq/cnetpub.h \
    base/office/cofficepub.h \
    base/regexp/regexppub.h \
    base/thread/cnetthreadpub.h \
    base/thread/cthreadpub.h \
    cppbase/include/cppbasetype.h \
    cppbase/include/readmacro.h \
    cppbase/include/testcase.h \
    cppbase/string/cstringpubcpp.h \
    libs/libzmq-v141-4_3_2/zmq.h \
    mainwindow.h \
    public/include/basetypepub.h \
    public/include/debugApp.h \
    public/include/expresspub.h \
    public/include/filepub.h \
    public/include/looppub.h \
    public/include/signpub.h \
    version.h

FORMS += \
    cdialogasktext.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/app.qrc

RC_FILE = \
    images/myapp.rc




DISTFILES += \
    images/myapp.rc \
    libs/libzmq-v141-4_3_2/libsodium.dll \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-4_3_2.dll \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-4_3_2.lib \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-s-4_3_2.lib
