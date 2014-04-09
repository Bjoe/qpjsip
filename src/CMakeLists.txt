
set(HEADERS
    engine.h
    accountconfiguration.h
    loggingconfiguration.h
    mediaconfiguration.h
    transportconfiguration.h
    pjerror.h
    callinfo.h
    accountinfo.h
)

if(${Qt4})
    set(QT_MOC_HEADERS
        engine.h
    )
    qt4_wrap_cpp(MOC_OUTFILES ${QT_MOC_HEADERS})
endif(${Qt4})

set(QT_SRCS
    engine.cpp
    accountconfiguration.cpp
    loggingconfiguration.cpp
    mediaconfiguration.cpp
    transportconfiguration.cpp
    pjerror.cpp
    callinfo.cpp
    accountinfo.cpp
)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qpjsua STATIC ${QT_SRCS} ${MOC_OUTFILES})

if(${Qt4})
  target_link_libraries(qpjsua ${QT_LIBRARIES} ${PJSIP_LIBRARIES}) # ${Boost_LIBRARIES})
else(${Qt4})
  target_link_libraries(qpjsua Qt5::Core ${PJSIP_LIBRARIES}) # ${Boost_LIBRARIES})
endif(${Qt4})

set_target_properties(qpjsua PROPERTIES
  PUBLIC_HEADER "${HEADERS};${CMAKE_CURRENT_BINARY_DIR}/config.h")
 
install(TARGETS qpjsua
  # IMPORTANT: Add the qpjsua library to the "export-set"
  EXPORT QpjSipTargets
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT dev)
