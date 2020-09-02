QT += widgets

TEMPLATE = lib

CONFIG += c++17

DEFINES += \
	ACCOUNT_LIBRARY \
	QT_DEPRECATED_WARNINGS \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000

HEADERS += \
	Account_global.h \
	Account.h \
	Item.h \

SOURCES += \
	Account.cpp \
	Item.cpp

FORMS += \
	Account.ui \
	Item.ui

include ($$PWD/../Json/Json.pri)

unix {
	target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32-msvc*:{
	QMAKE_CFLAGS *= /utf-8
	QMAKE_CXXFLAGS *= /utf-8
}
