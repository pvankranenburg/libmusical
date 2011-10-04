project(libmusical CXX)

cmake_minimum_required(VERSION 2.6)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3 -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()

add_subdirectory(libmusical)
add_subdirectory(applications)
#add_subdirectory(Documentation)
