# Minimum cmake version
cmake_minimum_required(VERSION 2.8)

# Name of the project
project(omega)

# Version of the project
set(omega_VERSION_MAJOR 0)
set(omega_VERSION_MINOR 91)

# Location of the custom cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#Quick & Dirty hack
add_definitions(-DBSD)

include(CheckLibraryExists)

find_package(Curses REQUIRED)
include_directories(SYSTEM ${CURSES_INCLUDE_DIR})

find_package(LuaJit REQUIRED)
include_directories(SYSTEM ${LUAJIT_INCLUDE_DIRS})

add_subdirectory(src)
