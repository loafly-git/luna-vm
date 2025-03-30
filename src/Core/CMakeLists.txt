add_library(jvm
SHARED
    BytecodeStream.cpp
    ClassLoader.cpp
)

target_link_libraries(jvm PRIVATE lnlog zip)
