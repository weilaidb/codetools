QT       += core gui
QT       += sql
QT       += network
QT       += multimedia

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

## release版本不输出
#DEFINES += QT_NO_DEBUG_OUTPUT


INCLUDEPATH += AStyle_3_1_windows/AStyle/src \
    public/include/ \
    base/msgtips/ \
    base/mysql/ \
    base/dialog/ \
    base/datetime/ \
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
    base/num/ \
    base/switch/ \
    base/algorithm/ \
    base/net/zeromq/ \
    base/network/ \
    base/multimedia/ \
    base/system/ \
    cppbase/string/ \
    cppbase/mutex/ \
    testcase/stringtest/ \

win32 {
#顾名思义，这里就是设置WIndows下的连接库，以及Visual C++2010编译器的的设置选项
#添加外部的引用头文件和库文件
INCLUDEPATH += \
    base/office/ \

#    libs/libzmq-v141-4_3_2 \


##$$PWD指当前路径， -l指定的文件去掉 .lib 以及 lib替换为l
#LIBS += -L$$PWD/libs/libzmq-v141-4_3_2  -lzmq-v141-mt-4_3_2



}

unix {
#原理和win32一样

}


macx {

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
    base/datetime/cdatetime.cpp \
    base/define/cdefinepub.cpp \
    base/dialog/cdialogpub.cpp \
    base/express/cexpresspub.cpp \
    base/log/clogpub.cpp \
    base/map/cdataprocess.cpp \
    base/map/cmappub.cpp \
    base/map/cprocessdata.cpp \
    base/msgtips/cmsgtips.cpp \
    base/multimedia/caudioplayer.cpp \
    base/mysql/csqlpub.cpp \
    base/net/zeromq/cnetpub.cpp \
    base/network/chttpwindow.cpp \
    base/network/cnetdiaglog.cpp \
    base/network/cnetworkpub.cpp \
    base/network/ctcpclientwindow.cpp \
    base/network/ctcpserverwindow.cpp \
    base/network/cudpmcastwindow.cpp \
    base/network/cudpwindow.cpp \
    base/num/cnumpub.cpp \
    base/office/cexcelpub.cpp \
    base/print/cprintpub.cpp \
    base/regexp/cregexppub.cpp \
    base/sign/csignpub.cpp \
    base/file/cfilepub.cpp \
    base/string/cstringpub.cpp \
    base/switch/clogsw.cpp \
    base/switch/clogswpub.cpp \
    base/switch/cswitchpub.cpp \
    base/system/ccmdwindow.cpp \
    base/system/csystempub.cpp \
    base/thread/cthreadextpub.cpp \
    base/ui/cuiextpub.cpp \
    base/ui/cuipub.cpp \
    base/thread/cnetthreadpub.cpp \
    base/thread/cthreadpub.cpp \
    base/tree/ctreepub.cpp \
    cdialogabout.cpp \
    cdialognewnode.cpp \
    cdialognewut.cpp \
    cdialogsearch.cpp \
    main.cpp \
    mainwindow.cpp \
    supertest.cpp \
    testcase/processtest/CProcessDataTest.cpp \
    testcase/stringtest/cstringpubcpp_main.cpp \
    testcase/virtualtest/cgrandmaster.cpp \
    testcase/virtualtest/cparent.cpp \
    testcase/virtualtest/cson.cpp

HEADERS += \
    AStyle_3_1_windows/AStyle/src/ASLocalizer.h \
    AStyle_3_1_windows/AStyle/src/astyle.h \
    AStyle_3_1_windows/AStyle/src/astyle_main.h \
    base/algorithm/calgorithmpub.h \
    base/codec/ctextcodecpub.h \
    base/datetime/cdatetime.h \
    base/define/cdefinepub.h \
    base/dialog/cdialogpub.h \
    base/express/cexpresspub.h \
    base/file/cfilepub.h \
    base/map/cbaseinterface.h \
    base/map/cdataprocess.h \
    base/map/cprocessdata.h \
    base/multimedia/caudioplayer.h \
    base/network/chttpwindow.h \
    base/network/cnetdiaglog.h \
    base/network/cnetworkpub.h \
    base/network/ctcpclientwindow.h \
    base/network/ctcpserverwindow.h \
    base/network/cudpmcastwindow.h \
    base/network/cudpwindow.h \
    base/num/cnumpub.h \
    base/office/cexcelpub.h \
    base/string/cstringpub.h \
    base/switch/clogsw.h \
    base/switch/clogswpub.h \
    base/switch/cswitchpub.h \
    base/system/ccmdwindow.h \
    base/system/csystempub.h \
    base/thread/cthreadextpub.h \
    base/ui/cuiextpub.h \
    base/ui/cuipub.h \
    base/log/clogpub.h \
    base/map/cmappub.h \
    base/msgtips/cmsgtips.h \
    base/mysql/csqlpub.h \
    base/net/zeromq/cnetpub.h \
    base/print/cprintpub.h \
    base/regexp/cregexppub.h \
    base/sign/csignpub.h \
    base/thread/cnetthreadpub.h \
    base/thread/cthreadpub.h \
    base/tree/ctreepub.h \
    cdialogabout.h \
    cdialognewnode.h \
    cdialognewut.h \
    cdialogsearch.h \
    libs/libzmq-v141-4_3_2/zmq.h \
    mainwindow.h \
    public/include/basedefinepub.h \
    public/include/basepub.h \
    public/include/basetypepub.h \
    public/include/debugApp.h \
    public/include/looppub.h \
    public/include/readmacro.h \
    supertest.h \
    testcase/stringtest/testcase.h \
    testcase/virtualtest/cgrandmaster.h \
    testcase/virtualtest/cparent.h \
    testcase/virtualtest/cson.h \
    version.h

win32 {
#顾名思义，这里就是设置WIndows下的连接库，以及Visual C++2010编译器的的设置选项
SOURCES += \
    base/office/cofficepub.cpp \
    base/mutex/cmutexpub.cpp \
    base/mutex/csempub.cpp \


HEADERS += \
    base/office/cofficepub.h \
    base/mutex/cmutexpub.h \
    base/mutex/csempub.h \

}

unix {

#原理和win32一样

}

macx {

}


FORMS += \
    cdialogabout.ui \
    cdialogasktext.ui \
    cdialognewnode.ui \
    cdialognewut.ui \
    cdialogsearch.ui \
    cnetdialog.ui \
    mainwindow.ui \
    supertest.ui \
    ui/audio/AudioPlayer.ui \
    ui/network/http.ui \
    ui/network/tcpclient.ui \
    ui/network/tcpserver.ui \
    ui/network/udp.ui \
    ui/network/udpmcast.ui \
    ui/system/cmd.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/app.qrc \
    ui/audio/res.qrc \
    ui/network/res.qrc

RC_FILE = \
    images/myapp.rc




DISTFILES += \
    doc/代码替换说明.txt \
    images/fohand.ico \
    images/myapp.rc \
    images/tools/CurRt.bmp \
    images/tools/ENV.bmp \
    images/tools/calc.bmp \
    images/tools/cmd.bmp \
    images/tools/excel.bmp \
    libs/libzmq-v141-4_3_2/libsodium.dll \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-4_3_2.dll \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-4_3_2.lib \
    libs/libzmq-v141-4_3_2/libzmq-v141-mt-s-4_3_2.lib \
    ui/audio/images/001.GIF \
    ui/audio/images/110.JPG \
    ui/audio/images/132.bmp \
    ui/audio/images/212.bmp \
    ui/audio/images/214.bmp \
    ui/audio/images/22.ico \
    ui/audio/images/224.bmp \
    ui/audio/images/23.ico \
    ui/audio/images/237.GIF \
    ui/audio/images/316.bmp \
    ui/audio/images/318.bmp \
    ui/audio/images/430.bmp \
    ui/audio/images/5.ico \
    ui/audio/images/610.bmp \
    ui/audio/images/612.bmp \
    ui/audio/images/616.bmp \
    ui/audio/images/620.bmp \
    ui/audio/images/622.bmp \
    ui/audio/images/624.bmp \
    ui/audio/images/630.bmp \
    ui/audio/images/632.bmp \
    ui/audio/images/828.bmp \
    ui/audio/images/Audio CD.ico \
    ui/audio/images/Movie Clip.ico \
    ui/audio/images/Recycle Bin empty.ico \
    ui/audio/images/Wave Sound.ico \
    ui/audio/images/audio_file.ico \
    ui/audio/images/music.ico \
    ui/audio/images/mute.bmp \
    ui/audio/images/volumn.bmp \
    ui/audio/music.ico \
    ui/network/images/051.JPG \
    ui/network/images/072.JPG \
    ui/network/images/075.JPG \
    ui/network/images/110.JPG \
    ui/network/images/132.bmp \
    ui/network/images/212.bmp \
    ui/network/images/620.bmp \
    ui/network/images/624.bmp \
    ui/network/images/826.bmp \
    ui/network/images/828.bmp
