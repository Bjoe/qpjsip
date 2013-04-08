
# i would to see more projects using these defaults
#ADD_DEFINITIONS( "-Wall" )
# ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

# Siehe http://developer.qt.nokia.com/wiki/UnitTesting
MACRO(qt_add_test testname testsrc)
     SET(test_${testname}_SRCS ${testsrc})

     SET(special_additional)
     FOREACH(_additional ${ARGN})
	  LIST(APPEND special_additional ${_additional})
     ENDFOREACH(_additional)
  
     if(NOT ${QT5})
        qt4_automoc(${test_${testname}_SRCS} ${special_additional})
     endif(NOT ${QT5})

     add_executable(test_${testname} ${test_${testname}_SRCS} ${special_additional} ${test_additional})
     target_link_libraries(test_${testname} ${test_additional_lib} ${QT_LIBRARIES})

     if(${QT5})
        qt5_use_modules(test_${testname} Test)
     endif(${QT5})
  
     add_test(test${testname} ${EXECUTABLE_OUTPUT_PATH}/test_${testname})

ENDMACRO()

MACRO(qt_test testname testsrc)
     SET(test_${testname}_SRCS ${testsrc})

     SET(special_additional)
     FOREACH(_additional ${ARGN})
	  LIST(APPEND special_additional ${_additional})
     ENDFOREACH(_additional)

     if(${QT5})
        qt5_wrap_cpp(test_${testname}_MOC ${test_${testname}_SRCS})
     else(${QT5})
        QT4_GET_MOC_FLAGS(moc_flags)
        GET_FILENAME_COMPONENT(test_${testname}_SRCS ${test_${testname}_SRCS} ABSOLUTE)
        QT4_MAKE_OUTPUT_FILE(${test_${testname}_SRCS} moc_ cpp test_${testname}_MOC)
        QT4_CREATE_MOC_COMMAND(${test_${testname}_SRCS} ${test_${testname}_MOC} "${moc_flags}" "")
     endif(${QT5})

     add_custom_target(moc_${testname}_target DEPENDS ${test_${testname}_MOC})
     add_executable(test_${testname} ${test_${testname}_SRCS} ${special_additional} ${test_additional})
     add_dependencies(test_${testname} moc_${testname}_target)
     target_link_libraries(test_${testname} ${test_additional_lib} ${QT_LIBRARIES})

     if(${QT5})
        qt5_use_modules(test_${testname} Test)
     endif(${QT5})
  
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
