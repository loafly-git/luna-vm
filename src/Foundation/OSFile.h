#pragma once

#include "Foundation/OSGenericFile.h"

#ifdef LUNA_PLATFORM_LINUX
#include "Foundation/OSPosixFile.h"
using OSFile = Luna::Foundation::OSPosixFile;
using OSFileHandle = Luna::Foundation::PosixFileHandle;
#endif
