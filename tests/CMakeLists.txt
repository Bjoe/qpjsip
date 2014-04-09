
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

set(CMAKE_AUTOMOC OFF)

if(${Qt4})
  find_package(Qt4 4.7.1  REQUIRED QtTest QtSql)
  include(${QT_USE_FILE})
else(${Qt4})
  # cmake example from http://qt-project.org/doc/qt-5.1/qtdoc/cmake-manual.html
  find_package(Qt5Test REQUIRED)
endif(${Qt4})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(
  "../src" 
  "${CMAKE_CURRENT_BINARY_DIR}/../src"
)

set(test_additional_lib
    qpjsua
#    ${PJSIP_LIBRARIES}
)

#set(test_additional
#    foo.cpp
#)

qt_test(example exampletest.cpp)
qt_test(accountConfiguration accountconfigurationtest.cpp)
qt_test(loggingConfiguration loggingconfigurationtest.cpp)
qt_test(mediaConfiguration mediaconfigurationtest.cpp)
qt_test(transportConfiguration transportconfigurationtest.cpp)
qt_test(pjerror pjerrortest.cpp)
qt_test(callInfo callinfotest.cpp)
qt_test(accountInfo accountinfotest.cpp)

# Maintest
if(${Qt4})
    qt4_wrap_cpp(MOC_OUTPUT output.h)
else(${Qt4})
    qt5_wrap_cpp(MOC_OUTPUT output.h)
endif(${Qt4})
add_executable(qpjsuaTest maintest.cpp output.cpp ${MOC_OUTPUT})

if(${Qt4})
  target_link_libraries(qpjsuaTest qpjsua ${QT_LIBRARIES}) #${PJSIP_LIBRARIES}  #${Boost_LIBRARIES})
else(${Qt4})
  target_link_libraries(qpjsuaTest qpjsua Qt5::Core) # ${PJSIP_LIBRARIES}) #${Boost_LIBRARIES})
endif(${Qt4})
