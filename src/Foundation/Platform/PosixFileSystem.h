#pragma once

#include "Common/Types.h"
#include "Foundation/GenericFileSystem.h"

namespace Luna::Fnd
{

class PosixFileHandle : public IFileHandle
{
public:
    ~PosixFileHandle();

    bool Read(uint8* Destination, uint32 Amount) const override;
    void Seek(ESeekOrigin Origin, uint32 Offset) const override;
    
    int Tell() const override;

    friend class PosixFileSystem;

private:
    FILE* FilePtr;
};

class PosixFileSystem : public IGenericFileSystem
{
public:
    ~PosixFileSystem() {}

    IFileHandle* Open(std::string      Path,
                      EFilePolicyFlags Flags,
                      bool             bForWrite = false) override;

    bool Exists(std::string Path) override;

    friend class PosixFileHandle;
};

} // namespace Luna::Foundation
