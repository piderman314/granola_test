cmake_minimum_required(VERSION 3.0)

project(granola)

file(GLOB granola_SRC "include/*.h" "src/*.cpp" "src/*.c")

add_library(granola STATIC ${granola_SRC})

target_include_directories(granola PUBLIC include)