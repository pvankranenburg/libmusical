project(libmusical CXX)
set (libmusical_VERSION_MAJOR 0)
set (libmusical_VERSION_MINOR 82)

cmake_minimum_required(VERSION 2.6)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3 -Wall")
endif()

add_subdirectory(libmusical)
add_subdirectory(applications)
#add_subdirectory(Documentation)

SET(CPACK_GENERATOR "TGZ")
SET(CPACK_SOURCE_GENERATOR "TGZ") 
SET(CPACK_PACKAGE_VERSION "0.9.1")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "9")
SET(CPACK_PACKAGE_VERSION_PATCH "1")

INCLUDE(CPack)

