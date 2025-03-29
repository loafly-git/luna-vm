#include "BytecodeStream.h"

#include <vector>

#include "Core/BytecodeStream.h"
#include "Common/Types.h"

using namespace Luna;

BytecodeStream::EResult BytecodeStream::LoadFromFile(std::string Path)
{
    return EResult::Ok;
}

bool LUNA_API BytecodeStream::IsBytecodeValid()
{
    return _Valid;
}

template<typename T>
bool BytecodeStream::GetUnsigned(uint32 Index, T& OutValue)
{
    static_assert(std::is_unsigned_v<T>, "T must be an unsigned integer");

    const unsigned long TotalIndex = (Index + sizeof(T)) - 1;
    if(TotalIndex < _Buffer.size())
    {
        return false;
    }

    OutValue = *reinterpret_cast<T*>(_Buffer.data()[Index]);
    return true;
}

// It might be better to move definition to the header
template bool BytecodeStream::GetUnsigned<uint8>(uint32 Index, uint8& OutValue);
template bool BytecodeStream::GetUnsigned<uint16>(uint32 Index, uint16& OutValue);
template bool BytecodeStream::GetUnsigned<uint32>(uint32 Index, uint32& OutValue);
template bool BytecodeStream::GetUnsigned<uint64>(uint32 Index, uint64& OutValue);
