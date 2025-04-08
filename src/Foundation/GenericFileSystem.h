#pragma once

#include <memory>
#include <string>

#include "Common/Types.h"

namespace Luna::Foundation
{

enum class ESeekOrigin
{
    //! Exactly set indicator position
    Set,
    //! Current
    Current,
    //! End of the file
    End
};

class IFileHandle
{
public:
    virtual ~IFileHandle()
    {
    }

    /**
     * Read the file into memory.
     * @param Destination Pointer to destination.
     * @param Amount      Amount of bytes to read.
     * @return            true on success, false otherwise.
     */
    virtual bool Read(uint8* Destination, uint32 Amount) const = 0;

    /**
     * Where to set the file position indicator
     * @param Origin Where to seek
     * @param Offset Offset relative to Origin (@ref ESeekOrigin)
     */
    virtual void Seek(ESeekOrigin Origin, uint32 Offset) const = 0;

    //! Gets the file indicator position
    virtual int Tell() const = 0;
};

enum EFilePolicyFlags : uint8
{
    //! None
    None          = 0,
    //! Prohibit other processes to request a write lock
    SharedLock    = 1 << 1,
    //! Request exclusive write access to the file
    ExclusiveLock = 1 << 2
};

class IGenericFileSystem
{
public:
    static IGenericFileSystem* Get() { return nullptr; }
    virtual ~IGenericFileSystem()
    {
    }

    virtual void SetParent(std::unique_ptr<IGenericFileSystem> Parent)
    {
        _Parent = std::move(Parent);
    }

    /**
     * Opens a file.
     * @param Path      Path to the file.
     * @param Flags     Accessing policy (@ref EFilePolicyFlags).
     * @param bForWrite Whether or not to open the file in write mode.
     * @return          Will return a non-nullptr pointer if succeeded.
     */
    virtual IFileHandle* Open(std::string      Path,
                              EFilePolicyFlags Flags,
                              bool             bForWrite = false) = 0;

    /**
     * Check for the existence of a file.
     * @param  Path Path to the file.
     * @return true if it exists, false if not.
     */
    virtual bool Exists(std::string Path) = 0;
private:
    std::unique_ptr<IGenericFileSystem> _Parent;
};

} // namespace Luna::Foundation
