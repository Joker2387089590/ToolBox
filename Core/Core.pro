QT += core gui widgets

CONFIG += c++17

TARGET = ToolBox

DEFINES += \
	QT_DEPRECATED_WARNINGS \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
	Core.cpp \
	Tray.cpp \
	main.cpp

HEADERS += \
	Core.h \
	Tray.h \
	UiCore.h

FORMS += \
	Core.ui

RESOURCES += \
	ico.qrc

# Include and dependence
include($$PWD/../Json/Json.pri)
INCLUDEPATH += \
	$$PWD/../Account \
	$$PWD/../Pics

DEPENDPATH += \
	$$PWD/../Account \
	$$PWD/../Pics

# Conditional compile
win32: CONFIG(debug, debug|release): {
	LIBS += \
		-L$$OUT_PWD/../Account/debug/ -lAccount \
		-L$$OUT_PWD/../Pics/debug/ -lPics
}
else: win32: CONFIG(release, debug|release): {
	LIBS += \
		-L$$OUT_PWD/../Account/release/ -lAccount \
		-L$$OUT_PWD/../Pics/release/ -lPics
	CONFIG += windeployqt
}
else: unix: {
	LIBS += \
		-L$$OUT_PWD/../Account/ -lAccount \
		-L$$OUT_PWD/../Pics/ -lPics
}

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32-msvc*: {
	QMAKE_CFLAGS *= /utf-8
	QMAKE_CXXFLAGS *= /utf-8
}
