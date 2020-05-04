
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qpjsua)

target_sources(qpjsua
PRIVATE
    engine.cpp
    accountconfiguration.cpp
    loggingconfiguration.cpp
    mediaconfiguration.cpp
    transportconfiguration.cpp
    pjerror.cpp
    callinfo.cpp
    accountinfo.cpp
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/engine.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/accountconfiguration.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/loggingconfiguration.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/mediaconfiguration.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/transportconfiguration.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/pjerror.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/callinfo.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/accountinfo.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/config.h>

    $<INSTALL_INTERFACE:include/engine.h>
    $<INSTALL_INTERFACE:include/accountconfiguration.h>
    $<INSTALL_INTERFACE:include/loggingconfiguration.h>
    $<INSTALL_INTERFACE:include/mediaconfiguration.h>
    $<INSTALL_INTERFACE:include/transportconfiguration.h>
    $<INSTALL_INTERFACE:include/pjerror.h>
    $<INSTALL_INTERFACE:include/callinfo.h>
    $<INSTALL_INTERFACE:include/accountinfo.h>
    $<INSTALL_INTERFACE:include/config.h>
)

target_compile_features(qpjsua PUBLIC cxx_std_17)
target_link_libraries(qpjsua PUBLIC Qt5::Core PkgConfig::PJSIP)
target_include_directories(qpjsua
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)
add_library(${namespace}::qpjsua ALIAS qpjsua)

install(FILES
    engine.h
    accountconfiguration.h
    loggingconfiguration.h
    mediaconfiguration.h
    transportconfiguration.h
    pjerror.h
    callinfo.h
    accountinfo.h
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS qpjsua
  EXPORT "${TARGETS_EXPORT_NAME}"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

