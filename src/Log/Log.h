#pragma once

#include <format>
#include <string_view>
#include <utility>

namespace Luna
{
    enum ELogLevel
    {
        Debug,
        Info,
        Warning,
        Error
    };

    void _LogImplementation(ELogLevel Level,
                            std::string&& File,
                            const unsigned int Line,
                            const std::string&& Message);

    template<typename... TArgs>
    void _Log(ELogLevel Level,
              const char* File,
              const unsigned int Line, 
              std::string_view Format, 
              TArgs&&... Args)
    {
        const std::string Text = std::vformat(Format,
                                              std::make_format_args(Args...));

        _LogImplementation(Level,
                           std::string(File),
                           Line,
                           std::move(Text));
    }
} // namespace Luna

#define _LNLOG(level, msg, ...) \
    Luna::_Log(level, __FILE__, __LINE__, msg __VA_ARGS__)

#ifdef NDEBUG
    #define LNLOGD(msg, ...) \
        _LNLOG(Luna::ELogLevel::Debug __VA_ARGS__)
#else
    #define LNLOGD(msg, ...)
#endif

#define LNLOGI(msg, ...) \
    _LNLOG(Luna::ELogLevel::Info, msg __VA_ARGS__)

#define LNLOGW(msg, ...) \
    _LNLOG(Luna::ELogLevel::Warning, msg __VA_ARGS__)

#define LNLOGE(msg, ...) \
    _LNLOG(Luna::ELogLevel::Error, msg __VA_ARGS__)
