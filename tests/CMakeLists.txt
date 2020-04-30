
find_package(Qt5 COMPONENTS Test REQUIRED)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
)

add_executable(exampleTest exampletest.cpp)
target_include_directories(exampleTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(exampleTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME exampleTest COMMAND exampleTest)

add_executable(accountConfigurationTest accountconfigurationtest.cpp)
target_include_directories(accountConfigurationTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(accountConfigurationTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME accountConfigurationTest COMMAND accountConfigurationTest)

add_executable(loggingConfigurationTest loggingconfigurationtest.cpp)
target_include_directories(loggingConfigurationTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(loggingConfigurationTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME loggingConfigurationTest COMMAND loggingConfigurationTest)

add_executable(mediaConfigurationTest mediaconfigurationtest.cpp)
target_include_directories(mediaConfigurationTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(mediaConfigurationTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME mediaConfigurationTest COMMAND mediaConfigurationTest)

add_executable(transportConfigurationTest transportconfigurationtest.cpp)
target_include_directories(transportConfigurationTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(transportConfigurationTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME transportConfigurationTest COMMAND transportConfigurationTest)

add_executable(pjerrorTest pjerrortest.cpp)
target_include_directories(pjerrorTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(pjerrorTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME pjerrorTest COMMAND pjerrorTest)

add_executable(callInfoTest callinfotest.cpp)
target_include_directories(callInfoTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(callInfoTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME callInfoTest COMMAND callInfoTest)

add_executable(accountInfoTest accountinfotest.cpp)
target_include_directories(accountInfoTest PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(accountInfoTest PUBLIC ${namespace}::qpjsua Qt5::Test)
add_test(NAME accountInfoTest COMMAND accountInfoTest)

add_executable(qpjsuaTest maintest.cpp output.cpp)
target_link_libraries(qpjsuaTest PUBLIC ${namespace}::qpjsua)
