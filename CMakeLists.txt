cmake_minimum_required(VERSION 3.21)

include(cmake/common.cmake)

project(lunavm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

option(USE_SYSTEM_LIBZIP "Whether to use system installed libzip" OFF)
option(LUNA_NO_SHARED    "Don't build a shared library" OFF)

string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -fvisibility=hidden")

# We don't want to set these if included via add_subdirectory
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

luna_package(libzip ${USE_SYSTEM_LIBZIP})

add_subdirectory(src)

# Install dirs
# Might be able to be moved to their respective CMakeLists?
install(TARGETS java
        RUNTIME DESTINATION bin)
install(TARGETS jvm
        LIBRARY DESTINATION lib)

