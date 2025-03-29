add_library(log
STATIC
    Log.cpp)

target_compile_definitions(log PRIVATE _FULL_SOURCE_PATH="${CMAKE_SOURCE_DIR}")
