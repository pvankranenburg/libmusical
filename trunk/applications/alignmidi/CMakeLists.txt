set(alignmidi_src alignmidi.cpp)

include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core ${CMAKE_SOURCE_DIR}/libmusical/specializations/midi ${CMAKE_SOURCE_DIR}/libmusical/CSUUMidiReader )

add_executable(alignmidi ${alignmidi_src})

target_link_libraries(alignmidi musical)

install(TARGETS alignmidi RUNTIME DESTINATION bin)
