#include "FileSystem.h"

#include <memory>
#include <utility>

#include "Foundation/GenericFileSystem.h"

using namespace Luna::Foundation;

#ifdef LUNA_PLATFORM_LINUX
#include "Foundation/Platform/PosixFileSystem.h"
using NativeFileSystem = PosixFileSystem;
#endif

void FileSystem::Initialize()
{
    _Root = std::make_unique<NativeFileSystem>();
}

IGenericFileSystem* FileSystem::_Get()
{
    return _Root.get();
}

void FileSystem::SetFileSystem(std::unique_ptr<IGenericFileSystem> FS)
{
    _Root->SetParent(std::move(FS));
}
