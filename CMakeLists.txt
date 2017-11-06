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
		catch
		GIT_REPOSITORY      https://github.com/Bareflank/catch.git
		GIT_TAG             v1.2
		GIT_SHALLOW         1
		CMAKE_ARGS          ${CATCH_CMAKE_ARGS}
		PREFIX              ${CMAKE_BINARY_DIR}/external/catch
		TMP_DIR             ${CMAKE_BINARY_DIR}/external/catch/tmp
		STAMP_DIR           ${CMAKE_BINARY_DIR}/external/catch/stamp
		DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/catch/download
		SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/catch/src
		BINARY_DIR          ${CMAKE_BINARY_DIR}/external/catch/build
		BUILD_COMMAND		""
	)

	ExternalProject_Get_Property(catch source_dir)
	set(CATCH_INCLUDE_DIR ${source_dir}/include CACHE INTERNAL "Path to include folder for catch")

	enable_testing()

	add_executable(granola_test "test/granola_test.cpp")
	target_include_directories(granola_test PRIVATE ${CATCH_INCLUDE_DIR})

	add_test(granola_test granola_test)
endif()