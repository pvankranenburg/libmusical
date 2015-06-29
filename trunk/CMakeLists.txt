project(libmusical C CXX)

#C only enabled for openmp test.
#Not needed if cmake version > 2.8.8

set (libmusical_VERSION_MAJOR 1)
set (libmusical_VERSION_MINOR 0)
set (libmusical_VERSION_PATCH 2)

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3 -Wall")
endif()

add_subdirectory(libmusical)
add_subdirectory(applications)
add_subdirectory(test)
#add_subdirectory(Documentation)

SET(CPACK_GENERATOR "TGZ")
SET(CPACK_SOURCE_GENERATOR "TGZ") 
SET(CPACK_PACKAGE_VERSION "1.0.3")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "3")

INCLUDE(CPack)

