#include <vector>

#include "Common/Types.h"

namespace Luna::Core
{

enum class EConstantType : uint8
{
    Class              = 7,
    FieldRef           = 9,
    MethodRef          = 10,
    InterfaceMethodRef = 11,

    String             = 8,
    Integer            = 3,
    Float              = 4,
    Long               = 5,
    Double             = 6,

    NameAndType        = 12,
    UTF8               = 1,
    MethodHandle       = 15,
    MethodType         = 16,
    InvokeDynamic      = 18
};

enum class EAccessFlag : uint16
{
    // Both shares these flags
    Public          = 0x0001,
    Final           = 0x0010,
    Synthetic       = 0x1000,
    Enum            = 0x4000,

    // Access flags used by classes
    ClassSuper      = 0x0020,
    ClassInterface  = 0x0200,
    ClassAbstract   = 0x0400,
    ClassAnnotation = 0x2000,

    // Access flags used by fields
    FieldPrivate    = 0x0002,
    FieldProtected  = 0x0004,
    FieldStatic     = 0x0008,
    FieldVolatile   = 0x0040,
    FieldTransient  = 0x0080

    // TODO: Method access flags
    // and probably move this whole thing
};

struct ClassFileInfo
{
    uint32 Magic;
    uint16 MinorVersion;
    uint16 MajorVersion;

    uint16 ConstantPoolCount;
    typedef struct {
        EConstantType Tag;
        uint8 Info;
    } ConstantPoolInfo;
    std::vector<ConstantPoolInfo> ConstantPool;
    EAccessFlag AccessFlag;

    uint16 ThisClass;
    uint16 SuperClass;

    uint16 InterfacesCount;
    std::vector<uint16> Interfaces;

    typedef struct {
        uint16 AttributeNameIndex;
        uint32 AttributeLength;
        std::vector<uint8> Info;
    } AttributeInfo;

    uint16 FieldsCount;
    typedef struct {
        EAccessFlag AccessFlags;
        uint16 NameIndex;
        uint16 DescriptorIndex;
        uint16 AttributesCount;
        std::vector<AttributeInfo> Attributes;
    } FieldInfo;
    std::vector<FieldInfo> Fields;

    uint16 MethodsCount;
    typedef struct {
        EAccessFlag AccessFlags;
        uint16 NameIndex;
        uint16 DescriptorIndex;
        uint16 AttributesCount;
        std::vector<AttributeInfo> Attributes;
    } MethodInfo;
    std::vector<MethodInfo> Methods;

    uint16 AttributesCount;
    std::vector<AttributeInfo> Attributes;
};

} // namespace Luna::Core




