cmake_minimum_required(VERSION 3.20)

project(lunavm)

string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra")

add_subdirectory(src)
