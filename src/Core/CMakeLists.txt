set(LIBNAME jvm)

set(SOURCE_LIST
    BytecodeStream.cpp
    ClassLoader.cpp
)

if(LUNA_NO_SHARED)
    add_library(${LIBNAME} STATIC ${SOURCE_LIST})
else()
    add_library(${LIBNAME} SHARED ${SOURCE_LIST})
endif()

target_link_libraries(jvm PRIVATE foundation lnlog zip)
