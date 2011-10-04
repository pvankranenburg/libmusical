set(musicaltest_src musicaltest.cpp)

include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core ${CMAKE_SOURCE_DIR}/libmusical/specializations/nlb )

add_executable(musicaltest ${musicaltest_src})

target_link_libraries(musicaltest musical)

install(TARGETS musicaltest RUNTIME DESTINATION bin)
