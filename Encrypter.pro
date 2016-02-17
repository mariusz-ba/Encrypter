#-------------------------------------------------
#
# Project created by QtCreator 2016-01-12T18:57:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Encrypter
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    encryption.cpp \
    encryptthread.cpp \
    encryptfilethread.cpp \
    aboutdialog.cpp

HEADERS  += widget.h \
    encryption.h \
    encryptthread.h \
    encryptfilethread.h \
    aboutdialog.h

FORMS    += widget.ui \
    aboutdialog.ui

INCLUDEPATH += E:/Crypto

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -LE:/cryptopp562/release/ -lCryptoPPLib
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/cryptopp562/debug/ -lCryptoPPLib
else:unix: LIBS += -L$$PWD/E:/cryptopp562/ -lCryptoPPLib

INCLUDEPATH += E:/cryptopp562
DEPENDPATH += E:/cryptopp562

RC_FILE = encrypter.rc
