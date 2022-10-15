cmake_minimum_required(VERSION 3.21)

function(group_sources)
	source_group("Form Files"     REGULAR_EXPRESSION ".*\\.ui")
	source_group("QML Files"      REGULAR_EXPRESSION ".*\\.qml")
	source_group("Resource Files" REGULAR_EXPRESSION ".*\\.qrc")
endfunction()
