QT += core gui widgets

TEMPLATE = lib

CONFIG += c++17

DEFINES += \
	PICS_LIBRARY \
	QT_DEPRECATED_WARNINGS \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000

HEADERS += \
	cgsort.h \
	hacg.h \
	pixiv.h \
	tabpage.h \
	widget.h

SOURCES += \
	cgsort.cpp \
	hacg.cpp \
	main.cpp \
	pixiv.cpp \
	tabpage.cpp \
	widget.cpp

FORMS += \
	cgsort.ui \
	hacg.ui \
	pixiv.ui \
	widget.ui

unix {
	target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32-msvc*:{
	QMAKE_CFLAGS *= /utf-8
	QMAKE_CXXFLAGS *= /utf-8
}

CONFIG(debug, debug|release){
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT
}

