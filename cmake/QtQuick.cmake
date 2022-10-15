cmake_minimum_required(VERSION 3.21)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools REQUIRED)

add_library(IQuick INTERFACE)

target_link_libraries(IQuick
	INTERFACE
	    Qt::Core
		Qt::Quick)

target_compile_definitions(IQuick
	INTERFACE
		$<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
