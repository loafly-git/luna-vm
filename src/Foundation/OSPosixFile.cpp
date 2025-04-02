#include "OSPosixFile.h"

#include <cassert>
#include <string>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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
    return true;
}

void PosixFileHandle::Seek(ESeekOrigin Origin, uint32 Offset) const
{

}

int PosixFileHandle::Tell() const
{
    assert(FilePtr != nullptr);

    const int Pos = ftell(FilePtr);
    return Pos;
}

PosixFileHandle* OSPosixFile::Open(std::string Path,
                                   EFilePolicyFlags Flags,
                                   bool bForWrite)
{
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
