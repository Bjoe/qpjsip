cmake_minimum_required(VERSION 2.8.9)

project(QPjSIP)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" CACHE PATH "cmake modul path") 
include(BuildUtil)

# The version number.
set(QPJSIP_VERSION_MAJOR 0)
set(QPJSIP_VERSION_MINOR 1)
set(QPJSIP_VERSION_PATCH 0)
set(QPJSIP_VERSION ${QPJSIP_VERSION_MAJOR}.${QPJSIP_VERSION_MINOR}.${QPJSIP_VERSION_PATCH})

# http://www.cmake.org/Wiki/CMake/Tutorials/How_to_create_a_ProjectConfig.cmake_file
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/QpjSip)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

  # Make relative paths absolute (needed later on)
foreach(p LIB INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

set(QT5 "false" CACHE BOOL "Qt5 build")
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
link_directories(${PJSIP_LIBRARY_DIRS})

include_directories("${PJSIP_INCLUDE_DIRS}" "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")

if(${DOC})
    find_doxygen()
endif(${DOC})

add_subdirectory(src)

if(${TEST})
    # The following are required to uses CTest, Dart and the Cdash dashboard
    enable_testing(true)
    include(CTest)
    add_subdirectory(tests)
endif(${TEST})

# Add all targets to the build-tree export set
export(TARGETS qpjsua
  FILE "${PROJECT_BINARY_DIR}/QpjSipTargets.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE QpjSip)
 
# Create the QpjSipConfig.cmake and QpjSipConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(QpjSipConfig.cmake.in
  "${PROJECT_BINARY_DIR}/QpjSipConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${QPJSIP_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(QpjSipConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/QpjSipConfig.cmake" @ONLY)
# ... for both
configure_file(QpjSipConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/QpjSipConfigVersion.cmake" @ONLY)
 
# Install the QpjSipConfig.cmake and QpjSipConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/QpjSipConfig.cmake"
  "${PROJECT_BINARY_DIR}/QpjSipConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
install(EXPORT QpjSipTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
