#pragma once

#include <string>

#include "Common/Types.h"

namespace Luna::Foundation
{

enum class ESeekOrigin
{
    //! Beginning of the file
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

class IOSGenericFile
{
public:
    virtual ~IOSGenericFile()
    {
    }

    /**
     * Opens a file.
     * @param Path      Path to the file.
     * @param Flags     Accessing policy (@ref EFilePolicyFlags).
     * @param bForWrite Whether or not to open the file in write mode.
     * @return          Will return a non-nullptr pointer if succeeded.
     */
    static IFileHandle* Open(std::string      Path,
                             EFilePolicyFlags Flags,
                             bool             bForWrite = false);
};

} // namespace Luna::Foundation
