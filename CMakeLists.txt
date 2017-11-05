cmake_minimum_required(VERSION 3.0)

project(granola)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	add_compile_options(/utf-8 /std:c++17)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-std=c++1z)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	add_compile_options(-std=c++1z)
endif()

file(GLOB granola_SRC "include/*.h" "src/*.cpp" "src/*.c")

add_library(granola ${granola_SRC})

target_include_directories(granola PUBLIC include)

if (test)
	include(ExternalProject)

	list(APPEND CATCH_CMAKE_ARGS
		"-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
	)

	ExternalProject_Add(
		googletest
		GIT_REPOSITORY      https://github.com/google/googletest.git
		GIT_TAG             release-1.7.0
		CMAKE_ARGS          ${CATCH_CMAKE_ARGS}
		PREFIX              ${CMAKE_BINARY_DIR}/external/googletest/prefix
		TMP_DIR             ${CMAKE_BINARY_DIR}/external/googletest/tmp
		STAMP_DIR           ${CMAKE_BINARY_DIR}/external/googletest/stamp
		DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/googletest/download
		SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/googletest/src
		BINARY_DIR          ${CMAKE_BINARY_DIR}/external/googletest/build
	)

	enable_testing()

	add_executable(granola_test "test/granola_test.cpp")
	add_dependencies(granola_test googletest)
	target_include_directories(granola_test PRIVATE include build/include)
	target_link_libraries(granola_test PRIVATE gtest gtest_main)

	add_test(granola_test granola_test)
endif()