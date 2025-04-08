#pragma once

/** @file **/

#include <memory>

#include "Common/Macros.h"
#include "Foundation/GenericFileSystem.h"

namespace Luna::Foundation
{

using FileHandle = IFileHandle;

class FileSystem
{
public:
    FileSystem()
    {
        Initialize();
    }

    //! Get a global instance
    static LUNA_API FileSystem& GetSelf()
    {
        static FileSystem Self;
        return            Self;
    }

    // Simply getter for the static Get()
    IGenericFileSystem* _Get();

    /**
     * Get the filesystem set by @ref SetFileSystem
     *
     * Note that the top of the hierarchy will always be the native fs
     * @return The object deriving IGenericFileSystem
     */
    static LUNA_API IGenericFileSystem* Get()
    {
        return FileSystem::GetSelf()._Get();
    }

    //! Set the parent of the native filesystem 
    void LUNA_API SetFileSystem(std::unique_ptr<IGenericFileSystem> FS);

    FileSystem(FileSystem const&)     = delete;
    void operator=(FileSystem const&) = delete;
private:
    void Initialize();

    std::unique_ptr<IGenericFileSystem> _Root;
};

} // namespace Luna::Foundation
