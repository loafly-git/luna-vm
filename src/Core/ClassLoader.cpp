#include "ClassLoader.h"

#include <memory>
#include <vector>

#include "Core/BytecodeStream.h"
#include "Common/Types.h"

using namespace Luna;

ClassLoader::EResult ClassLoader::LoadFromBytecodeStream(BytecodeStream& Stream)
{
    if(!Stream.IsBytecodeValid())
    {
        return ClassLoader::EResult::InvalidClassFile;
    }

    uint32 Magic;
    Stream.GetUnsigned<uint32>(0, Magic); 
    if(Magic != 0xCAFEBABE)
    {
        return ClassLoader::EResult::WrongMagic;
    }

    return ClassLoader::EResult::Ok;
}
