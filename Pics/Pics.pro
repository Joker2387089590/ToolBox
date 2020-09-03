QT += core gui widgets

TEMPLATE = lib

CONFIG += c++17

DEFINES += \
	PICS_LIBRARY \
	QT_DEPRECATED_WARNINGS \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000

HEADERS += \
	Pics.h \
	PicsGlobal.h \
	cgsort.h \
	hacg.h \
	pixiv.h \
	tabpage.h

SOURCES += \
	Pics.cpp \
	cgsort.cpp \
	hacg.cpp \
	main.cpp \
	pixiv.cpp \
	tabpage.cpp

FORMS += \
	Pics.ui \
	cgsort.ui \
	hacg.ui \
	pixiv.ui

unix {
	target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32-msvc*:{
	QMAKE_CFLAGS *= /utf-8
	QMAKE_CXXFLAGS *= /utf-8
}
