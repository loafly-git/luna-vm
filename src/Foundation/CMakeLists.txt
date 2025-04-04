add_library(foundation INTERFACE)

target_sources(foundation
INTERFACE
    FileSystem.cpp
    Platform/PosixFileSystem.cpp
)
