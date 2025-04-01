#pragma once

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
    virtual bool Read(uint8* Destination, uint32 Amount) = 0;

    /**
     * Where to set the file position indicator
     * @param Origin Where to seek
     * @param Offset Offset relative to Origin (@ref ESeekOrigin)
     */
    virtual void Seek(ESeekOrigin Origin, uint32 Offset) = 0;

    //! Gets the file indicator position
    virtual int Tell() = 0;
};

class IOSGenericFile
{
public:
    virtual ~IOSGenericFile()
    {
    }

    enum class EFilePolicyFlags : uint8
    {
        //! None
        None           = 0,
        //! Disallow other processes to read the file
        ExclusiveRead  = 0 << 1,
        //! Disallow other processes to write to the file
        ExclusiveWrite = 0 << 2
    };

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
};

} // namespace Luna::Foundation
