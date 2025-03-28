add_library(jvm
SHARED
    ClassLoader.cpp
)

target_link_libraries(jvm zip)
