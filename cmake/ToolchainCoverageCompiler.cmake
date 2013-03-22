# this one is important
SET(CMAKE_SYSTEM_NAME Linux)

find_program(CoverageCompiler_GCC csgcc)
find_program(CoverageCompiler_GXX csg++)
find_program(CoverageCompiler_AR csar)
find_program(CoverageCompiler_LD csld)

# specify the cross compiler
SET(CMAKE_C_COMPILER "${CoverageCompiler_GCC}"
    CACHE FILEPATH "CoverageCompiler wrapper" FORCE)
SET(CMAKE_CXX_COMPILER "${CoverageCompiler_GXX}"
    CACHE FILEPATH "CoverageCompiler wrapper" FORCE)
SET(CMAKE_LINKER "${CoverageCompiler_LD}"
    CACHE FILEPATH "CoverageCompiler wrapper" FORCE)
SET(CMAKE_AR "${CoverageCompiler_AR}"
    CACHE FILEPATH "CoverageCompiler wrapper" FORCE)
