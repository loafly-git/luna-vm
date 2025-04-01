if(NOT LUNA_NO_SHARED)
    set(type STATIC)
else()
    set(type SHARED)
endif()

add_library(jvm
${TYPE}
    BytecodeStream.cpp
    ClassLoader.cpp
)

target_link_libraries(jvm PRIVATE foundation lnlog zip)
