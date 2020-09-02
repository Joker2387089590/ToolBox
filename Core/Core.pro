QT += core gui widgets

CONFIG += c++17

DEFINES += \
	QT_DEPRECATED_WARNINGS \
	QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
	Tray.cpp \
	main.cpp \
	widget.cpp

HEADERS += \
	Tray.h \
	widget.h

FORMS += \
	widget.ui

RESOURCES += \
	ico.qrc

win32:CONFIG(release, debug|release): {
	LIBS += -L$$OUT_PWD/../Account/release/ -lAccount
	CONFIG += windeployqt
}
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Account/debug/ -lAccount
else:unix: LIBS += -L$$OUT_PWD/../Account/ -lAccount

include ($$PWD/../Json/Json.pri)
INCLUDEPATH += $$PWD/../Account
DEPENDPATH += $$PWD/../Account

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32-msvc*:{
	QMAKE_CFLAGS *= /utf-8
	QMAKE_CXXFLAGS *= /utf-8
}
