include_directories( ${CMAKE_SOURCE_DIR}/libmusical/core )

set(libmusical_test_lib_src
	TestReader.cpp
	TestSimilarityRater.cpp
	TestSymbol.cpp
)
add_library(testmusical SHARED ${libmusical_test_lib_src})
target_link_libraries(testmusical musical)


add_executable(TestAlignment TestAlignment.cpp)
target_link_libraries(TestAlignment testmusical)
target_link_libraries(TestAlignment musical)

add_test(TestAlignment ${CMAKE_CURRENT_BINARY_DIR}/TestAlignment)
