QT       += core gui
QT       += sql

win32 {
#顾名思义，这里就是设置WIndows下的连接库，以及Visual C++2010编译器的的设置选项
QT       += axcontainer
}

unix {

#原理和win32一样

}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += AStyle_3_1_windows/AStyle/src \
    public/include/ \
    base/msgtips/ \
    base/mysql/ \
    base/dialog/ \
    base/thread/ \
    base/regexp/ \
    base/express/ \
    base/return/ \
    base/define/ \
    base/sign/ \
    base/print/ \
    base/tree/ \
    base/map/ \
    base/codec/ \
    base/log/ \
    base/file/ \
    base/ui/ \
    base/string/ \
    base/algorithm/ \
    base/net/zeromq/ \
    cppbase/string/ \
    cppbase/mutex/ \
    testcase/stringtest/ \

win32 {
#顾名思义，这里就是设置WIndows下的连接库，以及Visual C++2010编译器的的设置选项
#添加外部的引用头文件和库文件
INCLUDEPATH += \
    base/office/ \
    libs/libzmq-v141-4_3_2 \


#$$PWD指当前路径， -l指定的文件去掉 .lib 以及 lib替换为l
LIBS += -L$$PWD/libs/libzmq-v141-4_3_2  -lzmq-v141-mt-4_3_2


}

unix {
#原理和win32一样

}


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
    base/algorithm/calgorithmpub.cpp \
    base/codec/ctextcodecpub.cpp \
    base/define/cdefinepub.cpp \
    base/dialog/cdialogpub.cpp \
    base/express/cexpresspub.cpp \
    base/log/clogpub.cpp \
    base/map/cmappub.cpp \
    base/msgtips/cmsgtips.cpp \
    base/mutex/cmutexpub.cpp \
    base/mutex/csempub.cpp \
    base/mysql/csqlpub.cpp \
    base/net/zeromq/cnetpub.cpp \
    base/print/cprintpub.cpp \
    base/regexp/cregexppub.cpp \
    base/return/creturnpub.cpp \
    base/sign/csignpub.cpp \
    base/file/cfilepub.cpp \
    base/string/cstringpub.cpp \
    base/ui/cuipub.cpp \
    base/thread/cnetthreadpub.cpp \
    base/thread/cthreadpub.cpp \
    base/tree/ctreepub.cpp \
    main.cpp \
    mainwindow.cpp \
    testcase/stringtest/cstringpubcpp_main.cpp

HEADERS += \
    AStyle_3_1_windows/AStyle/src/ASLocalizer.h \
    AStyle_3_1_windows/AStyle/src/astyle.h \
    AStyle_3_1_windows/AStyle/src/astyle_main.h \
    base/algorithm/calgorithmpub.h \
    base/codec/ctextcodecpub.h \
    base/define/cdefinepub.h \
    base/dialog/cdialogpub.h \
    base/express/cexpresspub.h \
    base/file/cfilepub.h \
    base/mutex/cmutexpub.h \
    base/mutex/csempub.h \
    base/string/cstringpub.h \
    base/ui/cuipub.h \
    base/log/clogpub.h \
    base/map/cmappub.h \
    base/msgtips/cmsgtips.h \
    base/mysql/csqlpub.h \
    base/net/zeromq/cnetpub.h \
    base/print/cprintpub.h \
    base/regexp/cregexppub.h \
    base/return/creturnpub.h \
    base/sign/csignpub.h \
    base/thread/cnetthreadpub.h \
    base/thread/cthreadpub.h \
    base/tree/ctreepub.h \
    libs/libzmq-v141-4_3_2/zmq.h \
    mainwindow.h \
    public/include/basedefinepub.h \
    public/include/basepub.h \
    public/include/basetypepub.h \
    public/include/debugApp.h \
    public/include/looppub.h \
    public/include/readmacro.h \
    testcase/stringtest/testcase.h \
    version.h

win32 {
#顾名思义，这里就是设置WIndows下的连接库，以及Visual C++2010编译器的的设置选项
SOURCES += \
    base/office/cofficepub.cpp \

HEADERS += \
    base/office/cofficepub.h \

}

unix {

#原理和win32一样

}



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
    doc/代码替换说明.txt \
    images/myapp.rc \
    libs/libzmq-v141-4_3_2/libsodium.dll \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-4_3_2.dll \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-4_3_2.lib \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-s-4_3_2.lib
