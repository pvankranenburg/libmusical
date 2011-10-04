set(musicaltest_src musicaltest.cpp)

add_definitions(-fopenmp)

INCLUDE(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-fopenmp HAVE_OPENMP)

IF(DEFINED HAVE_OPENMP)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
ENDIF(DEFINED HAVE_OPENMP)

include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core ${CMAKE_SOURCE_DIR}/libmusical/specializations/nlb )

add_executable(musicaltest ${musicaltest_src})

target_link_libraries(musicaltest musical)

install(TARGETS musicaltest RUNTIME DESTINATION bin)
