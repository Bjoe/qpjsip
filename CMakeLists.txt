cmake_minimum_required(VERSION 2.8.9)

project(QPjSIP)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" CACHE PATH "cmake modul path") 
include(BuildUtil)

# The version number.
set (Project_VERSION_MAJOR 0)
set (Project_VERSION_MINOR 1)
set (Project_VERSION_PATCH 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(QT5 "false" CACHE BOOL "Qt5 build")
if(${QT5})
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)

    # cmake example from http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html
    find_package(Qt5Core)

else(${QT5})

    find_package(Qt4 4.8 REQUIRED QtCore)
    include(${QT_USE_FILE})

endif(${QT5})


#SET(ENV{PKG_CONFIG_PATH} "foo/bar/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
find_package(PkgConfig)
pkg_check_modules(PJSIP libpjproject)
include_directories(${PJSIP_INCLUDE_DIRS})
link_directories(${PJSIP_LIBRARY_DIRS})

find_doxygen()

add_subdirectory(src)

if(${TEST})
    # The following are required to uses CTest, Dart and the Cdash dashboard
    enable_testing(true)
    include(CTest)
    add_subdirectory(tests)
endif(${TEST})
