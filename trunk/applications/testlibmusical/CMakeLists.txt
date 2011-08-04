set(musicaltest_src musicaltest.cpp)

include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core ${CMAKE_SOURCE_DIR}/libmusical/specializations/nlb )

add_definitions(-fopenmp)
SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " -fopenmp")

add_executable(musicaltest ${musicaltest_src})

target_link_libraries(musicaltest libmusical)
