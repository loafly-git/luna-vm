#pragma once

#include "Common/Types.h"
#include "Foundation/OSGenericFile.h"

namespace Luna::Foundation
{

class PosixFileHandle : public IFileHandle
{
public:
    ~PosixFileHandle();

    bool Read(uint8* Destination, uint32 Amount) const;
    void Seek(ESeekOrigin Origin, uint32 Offset) const;
    
    int Tell() const;

    friend class OSPosixFile;

private:
    FILE* FilePtr;
};

class OSPosixFile : public IOSGenericFile
{
public:
    ~OSPosixFile()
    {
    };

    static PosixFileHandle* Open(std::string Path,
                                 EFilePolicyFlags Flags,
                                 bool bForWrite = false) override;

    friend class PosixFileHandle;
};

} // namespace Luna::Foundation
