cmake_minimum_required(VERSION 3.18)
project(Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
group_sources()

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}
	COMPONENTS
		Widgets Quick LinguistTools
	REQUIRED)
include(QtQuick)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)
# file(GLOB_RECURSE FORMS *.ui)
file(GLOB_RECURSE QML_FILES *.qml)
file(GLOB_RECURSE TS_FILES *.ts)

qt_create_translation(QM_FILES ${PROJECT_SOURCE_DIR} ${TS_FILES})

add_executable(Core main.cpp)

qt_add_qml_module(Core
	URI
		Core
	VERSION
		0.1
	SOURCES
		Core.h
		Core.cpp
		UiData.h
		UiData.cpp
		Tray.h
		Tray.cpp
		${TS_FILES}
	RESOURCES
		resource/ToolBox.png
	QML_FILES
	    Core.qml
)

target_link_libraries(Core
	PUBLIC
		Qt::Widgets
		IQuick
		Utility
		ToolBox::Account
		ToolBox::ExeIndex
)
