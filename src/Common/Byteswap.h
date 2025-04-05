#pragma once

#include <concepts>

#include "Common/Types.h"

namespace
{
    struct Impl
    {
        template<typename T>
        T operator()(T Value);
    };
}

template<std::integral T>
T Byteswap(T Value)
{
    return Impl{}(Value);
}

template<>
[[maybe_unused]] uint8 Impl::operator()(uint8 Value)
{
    return Value;
}

/** GCC/Clang **/
#if defined(__GNUC__) || defined(__clang__)

template<>
[[maybe_unused]] uint16 Impl::operator()(uint16 Value)
{
    return __builtin_bswap16(Value);
}

template<>
[[maybe_unused]] uint32 Impl::operator()(uint32 Value)
{
    return __builtin_bswap32(Value);
}

template<>
[[maybe_unused]] uint64 Impl::operator()(uint64 Value)
{
    return __builtin_bswap64(Value);
}

#else

#error This is platform is unfamiliar to Luna...

#endif
