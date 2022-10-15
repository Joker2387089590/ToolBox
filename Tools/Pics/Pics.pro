QT += core gui widgets

TEMPLATE = lib

CONFIG += c++17

DEFINES += \
	PICS_LIBRARY \
	QT_DEPRECATED_WARNINGS \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000

HEADERS += PicsGlobal.h

include($$PWD/../TabPage.pri)
include($$PWD/Pics/Pics.pri)
include($$PWD/PicsWidget/PicsWidget.pri)

unix {
	target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32-msvc*:{
	QMAKE_CFLAGS *= /utf-8
	QMAKE_CXXFLAGS *= /utf-8
}
