
if(NOT ${QT5})
    set(QT_MOC_HEADERS
        engine.h
    )

    qt4_wrap_cpp(MOC_OUTFILES ${QT_MOC_HEADERS})

endif(NOT ${QT5})

set(HEADERS
    engine.h
    accountconfiguration.h
    loggingconfiguration.h
    mediaconfiguration.h
    transportconfiguration.h
    pjerror.h
)

set(QT_SRCS
    engine.cpp
    accountconfiguration.cpp
    loggingconfiguration.cpp
    mediaconfiguration.cpp
    transportconfiguration.cpp
    pjerror.cpp
)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qpjsua STATIC ${QT_SRCS} ${MOC_OUTFILES})

if(${QT5})
    qt5_use_modules(qpjsua Core)
endif(${QT5})

set_target_properties(qpjsua PROPERTIES
  PUBLIC_HEADER "${HEADERS};${CMAKE_CURRENT_BINARY_DIR}/config.h")
 
install(TARGETS qpjsua
  # IMPORTANT: Add the qpjsua library to the "export-set"
  EXPORT QpjSipTargets
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT dev)
