#pragma once

#include <string>
#include <vector>

#include "Common/Macros.h"
#include "Common/Types.h"

namespace Luna::Core
{

class LUNA_API BytecodeStream
{
public:
    enum class EResult
    {
        Ok,
        FileError
    };

    EResult LUNA_API LoadFromFile(std::string Path);

    bool LUNA_API IsBytecodeValid();

    template<typename T>
    bool LUNA_API GetUnsigned(uint32 Index, T& OutValue);
private:
    std::vector<uint8> _Buffer;

    bool _Valid;
};

} // namespace Luna::Core
