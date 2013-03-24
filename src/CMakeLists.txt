
set(QT_MOC_HEADERS
#    mainwindow.h
)

set(QT_UI
#    mainwindow.ui
)

set(QT_SRCS
#    mainwindow.cpp
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

qt4_wrap_cpp(MOC_OUTFILES ${QT_MOC_HEADERS})

# Die ui_xxxx.h files werden im CMAKE_CURRENT_BINARY_DIR erzeugt.
#qt4_wrap_ui(UI_OUTFILES ${QT_UI})

add_library(qpjsua STATIC ${QT_SRCS} ${UI_OUTFILES} ${MOC_OUTFILES})
