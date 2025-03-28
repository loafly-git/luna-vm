#include <vector>

#include "Common/Types.h"
#include "Common/CompilerDefs.h"

namespace Luna
{

enum class EConstantType : u8
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

enum class EAccessFlag : u16
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

#pragma pack(1)

struct ClassFileInfo
{
    u32 Magic;
    u16 MinorVersion;
    u16 MajorVersion;

    u16 ConstantPoolCount;
    typedef struct {
        EConstantType Tag;
        u8 Info;
    } ConstantPoolInfo;
    std::vector<ConstantPoolInfo> ConstantPool;
    EAccessFlag AccessFlag;

    u16 ThisClass;
    u16 SuperClass;

    u16 InterfacesCount;
    std::vector<u16> Interfaces;

    typedef struct {
        u16 AttributeNameIndex;
        u32 AttributeLength;
        std::vector<u8> Info;
    } AttributeInfo;

    u16 FieldsCount;
    typedef struct {
        EAccessFlag AccessFlags;
        u16 NameIndex;
        u16 DescriptorIndex;
        u16 AttributesCount;
        std::vector<AttributeInfo> Attributes;
    } FieldInfo;
    std::vector<FieldInfo> Fields;

    u16 MethodsCount;
    typedef struct {
        EAccessFlag AccessFlags;
        u16 NameIndex;
        u16 DescriptorIndex;
        u16 AttributesCount;
        std::vector<AttributeInfo> Attributes;
    } MethodInfo;
    std::vector<MethodInfo> Methods;

    u16 AttributesCount;
    std::vector<AttributeInfo> Attributes;
};

} // namespace Luna

#pragma options align=reset
