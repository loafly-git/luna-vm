#pragma once

#include <string_view>
#include <vector>

#include "Common/Types.h"

namespace Luna::Core
{

namespace FileSystem
{
    enum class EResult
    {
        Ok,
        FileNotFound
    };

    EResult ReadToU8Buffer(std::string_view Path, std::vector<uint8>& Buffer);
};

} // namespace Luna
