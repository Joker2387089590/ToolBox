TEMPLATE = subdirs

SUBDIRS += \
	Core \
	Account \
	Pics

Core.depends = Account Pics
