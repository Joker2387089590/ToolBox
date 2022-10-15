cmake_minimum_required(VERSION 3.21)
project(ExeIndex)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
group_sources()

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Qml REQUIRED)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
	set(UacLinkFlag /level='requireAdministrator')
else()
	set(UacLinkFlag "/MANIFESTUAC:level='requireAdministrator'")
endif()

add_executable(LinkMaker LinkMaker.cpp)
target_link_options(LinkMaker PRIVATE ${UacLinkFlag})

qt_add_qml_module(ExeIndex
	URI
		Tools.ExeIndex
	VERSION
		0.1
	SOURCES
		ExeIndex.h
		ExeIndex.cpp
	QML_FILES
		ExeIndex.qml
	STATIC
)

add_library(ToolBox::ExeIndex ALIAS ExeIndex)
