#pragma once

#include <format>
#include <string>
#include <string_view>
#include <utility>

#include "Common/Macros.h"

namespace Luna::Log
{
    enum ELogLevel
    {
        Debug,
        Info,
        Warning,
        Error
    };

    void LUNA_API _LogImplementation(ELogLevel Level,
                                     std::string&& File,
                                     const unsigned int Line,
                                     const std::string&& Message);

    template<typename... TArgs>
    void _Log(ELogLevel Level,
              const char* File,
              const unsigned int Line, 
              const std::string_view Format, 
              TArgs&&... Args)
    {
        const std::string Text = std::vformat(Format,
                                              std::make_format_args(Args...));

        _LogImplementation(Level,
                           std::string(File),
                           Line,
                           std::move(Text));
    }
} // namespace Luna::Log

#define _LNLOG(level, msg, ...) \
    Luna::Log::_Log(level, __FILE__, __LINE__, msg, ##__VA_ARGS__)

#ifndef NDEBUG
    #define LNLOGD(msg, ...) \
        _LNLOG(Luna::Log::ELogLevel::Debug, msg, ##__VA_ARGS__)
#else
    #define LNLOGD(msg, ...)
#endif

#define LNLOGI(msg, ...) \
    _LNLOG(Luna::Log::ELogLevel::Info, msg, ##__VA_ARGS__)

#define LNLOGW(msg, ...) \
    _LNLOG(Luna::Log::ELogLevel::Warning, msg, ##__VA_ARGS__)

#define LNLOGE(msg, ...) \
    _LNLOG(Luna::Log::ELogLevel::Error, msg, ##__VA_ARGS__)
