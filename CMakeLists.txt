cmake_minimum_required(VERSION 3.21)
project(ToolBox VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(GroupSources)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")
add_compile_definitions("$<$<C_COMPILER_ID:MSVC>:UNICODE>")
add_compile_definitions("$<$<CXX_COMPILER_ID:MSVC>:UNICODE>")

add_subdirectory(Utility)
add_subdirectory(Tools/ExeIndex)
add_subdirectory(Tools/Account)
add_subdirectory(Core)
