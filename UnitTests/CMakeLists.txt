cmake_minimum_required(VERSION 2.6)
project(unittests)

include_directories("..")

add_executable(unittests main.cpp)

install(TARGETS unittests RUNTIME DESTINATION bin)
