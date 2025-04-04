#include "PosixFileSystem.h"

#include <cassert>
#include <string>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Common/Types.h"
#include "Log/Log.h"

using namespace Luna::Foundation;

PosixFileHandle::~PosixFileHandle()
{
    if(FilePtr)
    {
        fclose(FilePtr);
    }
}

bool PosixFileHandle::Read(uint8* Destination, uint32 Amount) const
{
    const size_t RetVal = fread(Destination, sizeof(uint8), Amount, FilePtr);
    if(RetVal == Amount)
    {
        return true;
    } else
    {
        if(feof(FilePtr))
        {
            LNLOGE("fread() failed (unexpected EOF)");
        } else if(ferror(FilePtr))
        {
            LNLOGE("fread() failed");
        }
        return false;
    }

    // Unreachable
    return false;
}

static inline int GetOrigin(ESeekOrigin Origin)
{
    switch(Origin)
    {
        case ESeekOrigin::Set:
            return SEEK_SET;
        case ESeekOrigin::Current:
            return SEEK_CUR;
        case ESeekOrigin::End:
            return SEEK_END;
    }

    return 0;
}

void PosixFileHandle::Seek(ESeekOrigin Origin, uint32 Offset) const
{
    const int OriginValue = GetOrigin(Origin);

    if(fseek(FilePtr, Offset, OriginValue) != 0)
    {
        LNLOGE("fseek() failed");
    }
}

int PosixFileHandle::Tell() const
{
    const int Pos = ftell(FilePtr);
    return Pos;
}

IFileHandle* PosixFileSystem::Open(std::string Path,
                                   EFilePolicyFlags Flags,
                                   bool bForWrite)
{
    // Is file locking really necessary?
    // Might just get rid of them...

    PosixFileHandle* FileHandle = new PosixFileHandle;

    std::string Mode = "rb";
    if(bForWrite)
    {
        Mode = "wb";
    }

    FileHandle->FilePtr = fopen(Path.c_str(), Mode.c_str());
    if(FileHandle->FilePtr == nullptr)
    {
        LNLOGE("Opening file {} failed!", Path);
        delete FileHandle;

        return nullptr;
    }

    bool bWithLock = false;
    struct flock FLock;

    FLock.l_whence = SEEK_SET;
    FLock.l_start  = 0;
    FLock.l_len    = 0;

    if(Flags & EFilePolicyFlags::SharedLock)
    {
        FLock.l_type = F_RDLCK;
        bWithLock = true;
    } else if(Flags & EFilePolicyFlags::ExclusiveLock)
    {
        FLock.l_type = F_WRLCK;
        bWithLock = true;
    }

    if(bWithLock)
    {
        const int FileNo = fileno(FileHandle->FilePtr);
        // Failing to lock hopefully shouldn't be too much of a problem
        // So for now, let's just log a warning
        if(fcntl(FileNo, F_SETLKW, &FLock) == -1)
        {
            LNLOGW("Failed to acquire file lock! {}", strerror(errno));
        }
    }

    return FileHandle;
}

bool PosixFileSystem::Exists(std::string Path)
{
    if(access(Path.c_str(), F_OK) == 0)
    {
        return true;
    }

    return false;
}
