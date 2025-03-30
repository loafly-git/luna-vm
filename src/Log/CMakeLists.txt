add_library(lnlog INTERFACE)

target_sources(lnlog
INTERFACE
    Log.cpp
)

target_compile_definitions(lnlog INTERFACE _FULL_SOURCE_PATH="${CMAKE_SOURCE_DIR}")
