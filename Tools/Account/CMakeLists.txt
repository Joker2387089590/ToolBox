cmake_minimum_required(VERSION 3.21)
project(Account)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
group_sources()

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Qml REQUIRED)

qt_add_qml_module(Account
	URI
		Tools.Account
	VERSION
		0.1
	SOURCES
		Account.cpp
		Account.h
	QML_FILES
		Account.qml
	RESOURCES
	    new-info.json
	STATIC
)

target_link_libraries(Account)
add_library(ToolBox::Account ALIAS Account)
