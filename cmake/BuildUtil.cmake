
# i would to see more projects using these defaults
#ADD_DEFINITIONS( "-Wall" )
# ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

MACRO(qt_test testname testsrc)
     SET(test_${testname}_SRCS ${testsrc})

     SET(special_additional)
     FOREACH(_additional ${ARGN})
      LIST(APPEND special_additional ${_additional})
     ENDFOREACH(_additional)

     if(${Qt4})
        qt4_automoc(${test_${testname}_SRCS} ${special_additional})
     else(${Qt4})
        qt5_wrap_cpp(test_${testname}_MOC ${test_${testname}_SRCS})
        add_custom_target(moc_${testname}_target DEPENDS ${test_${testname}_MOC})
     endif(${Qt4})
     
     add_executable(test_${testname} ${test_${testname}_SRCS} ${special_additional} ${test_additional})

     if(${Qt4})
        target_link_libraries(test_${testname} ${test_additional_lib} ${QT_LIBRARIES})
     else(${Qt4})
        add_dependencies(test_${testname} moc_${testname}_target)
        target_link_libraries(test_${testname} ${test_additional_lib} Qt5::Test)
     endif(${Qt4})
     
     add_test(test${testname} ${EXECUTABLE_OUTPUT_PATH}/test_${testname})
ENDMACRO()

# http://snikt.net/index.php/2010/04/01/howto-use-cmake-with-cc-projects
MACRO(find_doxygen)
    # check if doxygen is even installed
    find_package(Doxygen) # REQUIRED)

    if(EXISTS ${DOXYGEN_EXECUTABLE})
        # prepare doxygen configuration file
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

        # add doxygen as target
        add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

        # cleanup $build/api-doc on "make clean"
        set_property(DIRECTORY APPEND PROPERTY
             ADDITIONAL_MAKE_CLEAN_FILES api-doc)

        # add doxygen as dependency to doc-target
        get_target_property(DOC_TARGET doc TYPE)
        if(NOT DOC_TARGET)
            add_custom_target(doc)
        endif()
        add_dependencies(doc doxygen)

        # install HTML API documentation and manual pages
        set(DOC_PATH "share/doc/${CPACK_PACKAGE_NAME}-${VERSION}")
        #
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/html
                 DESTINATION ${DOC_PATH}
               )
        #
        # install man pages into packages, scope is now project root..
         install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/man/man3
                  DESTINATION share/man/man3/
                )
    endif()
ENDMACRO()

FUNCTION(add_assembler_output _target)
    ADD_DEFINITIONS( "-save-temps" )
    add_custom_target(lss COMMAND objdump -h -S ${_target} >${_target}.lss DEPENDS ${_target})
    #add_custom_command(TARGET ${_target} COMMAND objdump -h -S ${_target} >${_target}.lss)
ENDFUNCTION()
