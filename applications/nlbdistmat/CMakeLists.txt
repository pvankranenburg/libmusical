set(nlbdistmat_src nlbdistmat.cpp)

#INCLUDE(CheckCXXCompilerFlag)
#check_cxx_compiler_flag(-fopenmp HAVE_OPENMP)
#
#if(HAVE_OPENMP)
#	add_definitions(-fopenmp)
#	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
#endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core ${CMAKE_SOURCE_DIR}/libmusical/specializations/nlb )

add_executable(nlbdistmat ${nlbdistmat_src})

target_link_libraries(nlbdistmat musical)

install(TARGETS nlbdistmat RUNTIME DESTINATION bin)

