#include <memory>
#include <vector>

#include "Core/ClassFile.h"
#include "Common/Types.h"

namespace Luna::Core
{

class BytecodeStream;

class ClassLoader
{
public:
    enum class EResult
    {
        Ok,
        InvalidBytecodeStream,
        InvalidClassFile,
        WrongMagic
    };

    EResult LoadFromBytecodeStream(BytecodeStream& Stream);

    inline ClassFileInfo& GetClassFileInfo() const;

private:
    ClassFileInfo _ClassFile{};
};

} // namespace Luna::Core
