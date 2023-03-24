set(alignpitchcontext_src alignpitchcontext.cpp)

INCLUDE(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-fopenmp HAVE_OPENMP)

if(HAVE_OPENMP)
	#add_definitions(-fopenmp)
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
endif()

include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core ${CMAKE_SOURCE_DIR}/libmusical/specializations/pitchcontext )

add_executable(alignpitchcontext ${alignpitchcontext_src})

target_link_libraries(alignpitchcontext musical)

install(TARGETS alignpitchcontext RUNTIME DESTINATION bin)

