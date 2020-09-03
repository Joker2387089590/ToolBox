TEMPLATE = subdirs

SUBDIRS += \
	Core \
	Account \
	Pics

include($$PWD/Json/Json.pri)

Core.depends += Account Pics
