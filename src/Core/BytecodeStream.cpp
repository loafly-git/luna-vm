#include "BytecodeStream.h"

#include <iostream>
#include <string>
#include <vector>

#include "Common/Byteswap.h"
#include "Common/Types.h"
#include "Core/BytecodeStream.h"
#include "Foundation/FileSystem.h"

using namespace Luna::Core;
using namespace Luna::Foundation;

BytecodeStream::EResult BytecodeStream::LoadFromFile(std::string Path)
{
    FileHandle* File = FileSystem::Get()->Open(Path,
                                               EFilePolicyFlags::SharedLock);

    if(File == nullptr)
    {
        return EResult::FileError;
    }

    File->Seek(ESeekOrigin::End, 0);
    const int Size = File->Tell();

    _Buffer.reserve(Size);
    // We need to call this, otherwise size() will return 0
    _Buffer.resize(Size);

    File->Seek(ESeekOrigin::Set, 0);
    const bool Success = File->Read(_Buffer.data(), Size);

    if(!Success)
    {
        return EResult::FileError;
    }

    return EResult::Ok;
}

bool BytecodeStream::IsBytecodeValid()
{
    // TODO bytecode verification
    return _Valid;
}

template<typename T>
bool BytecodeStream::GetUnsigned(uint32 Index, T& OutValue)
{
    static_assert(std::is_unsigned_v<T>, "T must be of type unsigned");

    const unsigned long TotalIndex = (Index + sizeof(T)) - 1;
    if(TotalIndex > _Buffer.size())
    {
        return false;
    }

    OutValue = *reinterpret_cast<T*>(&_Buffer.data()[Index]);
    return true;
}

// It might be better to move definition to the header
template bool BytecodeStream::GetUnsigned<uint8>(uint32 Index, uint8& OutValue);
template bool BytecodeStream::GetUnsigned<uint16>(uint32 Index, uint16& OutValue);
template bool BytecodeStream::GetUnsigned<uint32>(uint32 Index, uint32& OutValue);
template bool BytecodeStream::GetUnsigned<uint64>(uint32 Index, uint64& OutValue);
