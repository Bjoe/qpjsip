cmake_minimum_required(VERSION 2.8)

project(QPjSIP)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" CACHE PATH "cmake modul path") 
include(BuildUtil)

# The version number.
set (Project_VERSION_MAJOR 0)
set (Project_VERSION_MINOR 1)
set (Project_VERSION_PATCH 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4 4.8 REQUIRED QtCore QtGui)

include(${QT_USE_FILE})

#SET(ENV{PKG_CONFIG_PATH} "foo/bar/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
find_package(PkgConfig)
pkg_check_modules(PJSIP libpjproject)
include_directories(${PJSIP_INCLUDE_DIRS})
link_directories(${PJSIP_LIBRARY_DIRS})

find_doxygen()

add_subdirectory(src)

set(NOTEST "false" CACHE BOOL "Without tests")
if(NOT ${NOTEST})
    # The following are required to uses CTest, Dart and the Cdash dashboard
    enable_testing(true)
    include(CTest)
    add_subdirectory(tests)
endif(NOT ${NOTEST})
