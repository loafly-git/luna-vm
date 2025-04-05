cmake_minimum_required(VERSION 3.21)

include(cmake/common.cmake)

project(lunavm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

option(USE_SYSTEM_LIBZIP "Whether to use system installed libzip" OFF)
option(LUNA_NO_SHARED    "Don't build a shared library" OFF)

# Option for Clang LTO
option(ENABLE_CLANG_LTO "Enable Clang Link Time Optimization" OFF)

# We don't want to set these if included via add_subdirectory
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -fvisibility=hidden")
endif()

# Enable LTO if requested and if using Clang
if(ENABLE_CLANG_LTO AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
     message(STATUS "Clang detected and LTO enabled")
     set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
     add_compile_options("-flto")
     add_link_options("-flto")
endif()

luna_package(libzip ${USE_SYSTEM_LIBZIP})

# Print options
message(STATUS "USE_SYSTEM_LIBZIP=${USE_SYSTEM_LIBZIP}")
message(STATUS "LUNA_NO_SHARED=${LUNA_NO_SHARED}")

if(LUNA_NO_SHARED)
    message(STATUS "Building as static library")
else()
    add_compile_definitions(LUNA_BUILD_DSO=1)
endif()

if(UNIX AND NOT APPLE)
    add_compile_definitions(LUNA_PLATFORM_LINUX)
endif()

add_subdirectory(src)

# Install dirs
# Might be able to be moved to their respective CMakeLists?
install(TARGETS java
        RUNTIME DESTINATION bin)
install(TARGETS jvm
        LIBRARY DESTINATION lib)
