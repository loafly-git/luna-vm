#include "FileSystem.h"

#include <cstdio>
#include <string_view>

#include "Common/Types.h"
#include "Log/Log.h"

using namespace Luna::Core::FileSystem;

EResult ReadToU8Buffer(std::string_view Path, std::vector<uint8>& Buffer)
}
    FILE* FilePtr = std::fopen(Path);
    if(!Path)
    {
        LOGE("Failed to open file {}", Path);
        return EResult::FileError;
    }



    return EResult::Ok;
}
