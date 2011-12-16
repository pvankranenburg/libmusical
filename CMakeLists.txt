project(libmusical CXX)
set (libmusical_VERSION_MAJOR 0)
set (libmusical_VERSION_MINOR 10)
set (libmusical_VERSION_PATCH x)

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-g -Wall")
endif()

add_subdirectory(libmusical)
add_subdirectory(applications)
add_subdirectory(test)
#add_subdirectory(Documentation)

SET(CPACK_GENERATOR "TGZ")
SET(CPACK_SOURCE_GENERATOR "TGZ") 
SET(CPACK_PACKAGE_VERSION "0.10.x")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "10")
SET(CPACK_PACKAGE_VERSION_PATCH "x")

INCLUDE(CPack)

