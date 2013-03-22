
SET(COVERAGE_FLAGS "--cs-on --cs-count --cs-qt4 --cs-exclude-file-regex=ui_.* --cs-exclude-file-regex=qrc_.* --cs-full-instrumentation --cs-output=${PROJECT_BINARY_DIR}/coverage")
SET(CMAKE_CXX_FLAGS_COVERAGE 
      "${CMAKE_C_FLAGS_RELEASE} ${COVERAGE_FLAGS}" CACHE STRING 
      "Flags used by the C++ compiler during coverage builds." FORCE )
SET(CMAKE_C_FLAGS_COVERAGE
      "${CMAKE_CXX_FLAGS_RELEASE} ${COVERAGE_FLAGS}" CACHE STRING
      "Flags used by the C compiler during coverage builds." FORCE )
SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE
      "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${COVERAGE_FLAGS}" CACHE STRING
      "Flags used for linking binaries during coverage builds." FORCE )
SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
      "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${COVERAGE_FLAGS}" CACHE STRING
      "Flags used by the shared libraries linker during coverage builds." FORCE )
SET(CMAKE_STATIC_LINKER_FLAGS_COVERAGE
      "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} ${COVERAGE_FLAGS}" CACHE STRING
      "Flags used by the static libraries linker during coverage builds." FORCE )

MARK_AS_ADVANCED(
      CMAKE_CXX_FLAGS_COVERAGE
      CMAKE_C_FLAGS_COVERAGE
      CMAKE_EXE_LINKER_FLAGS_COVERAGE
      CMAKE_SHARED_LINKER_FLAGS_COVERAGE
      CMAKE_STATIC_LINKER_FLAGS_COVERAGE
      COMPILE_DEFINITIONS_COVERAGE
)
