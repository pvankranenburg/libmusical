set(alignnlb_src alignnlb.cpp)

INCLUDE(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-fopenmp HAVE_OPENMP)

if(HAVE_OPENMP)
	add_definitions(-fopenmp)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
endif()

include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core ${CMAKE_SOURCE_DIR}/libmusical/specializations/nlb )

add_executable(alignnlb ${alignnlb_src})

target_link_libraries(alignnlb musical)

install(TARGETS alignnlb RUNTIME DESTINATION bin)

