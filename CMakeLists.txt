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
	
	list(APPEND DOCTEST_CMAKE_ARGS
		"-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
	)

	ExternalProject_Add(
		doctest
		GIT_REPOSITORY      https://github.com/onqtam/doctest.git
		GIT_TAG             1.2.6
		CMAKE_ARGS          ${DOCTEST_CMAKE_ARGS}
		PREFIX              ${CMAKE_BINARY_DIR}/external/doctest/prefix
		TMP_DIR             ${CMAKE_BINARY_DIR}/external/doctest/tmp
		STAMP_DIR           ${CMAKE_BINARY_DIR}/external/doctest/stamp
		DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/doctest/download
		SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/doctest/src
		BINARY_DIR          ${CMAKE_BINARY_DIR}/external/doctest/build
	)

	enable_testing()

	add_executable(granola_test "test/granola_test.cpp")
	add_dependencies(granola_test doctest)
	target_include_directories(granola_test PRIVATE build/include)

	add_test(granola_test granola_test)
endif()