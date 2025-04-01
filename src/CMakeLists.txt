# Start your includes from this dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(NOT LUNA_NO_SHARED)
    add_compile_definitions(LUNA_BUILD_DSO)
else()
    message(INFO "Building static library")
endif()

add_subdirectory(Foundation)
add_subdirectory(Log)
add_subdirectory(Core)
add_subdirectory(CLI)
