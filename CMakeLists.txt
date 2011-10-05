project(libmusical CXX)

cmake_minimum_required(VERSION 2.6)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3 -Wall")
endif()

add_subdirectory(libmusical)
add_subdirectory(applications)
#add_subdirectory(Documentation)

SET(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ") 
INCLUDE(CPack)


