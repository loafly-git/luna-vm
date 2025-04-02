#include "Log.h"

#include <format>
#include <iostream>
#include <string>
#include <string_view>

#include "Common/Macros.h"

using namespace Luna::Log;

static inline std::string GetLevelString(ELogLevel Level)
{
    switch(Level)
    {
    #define LEVEL(x) \
        case ELogLevel::x: \
            return #x;

        LEVEL(Debug)
        LEVEL(Info)
        LEVEL(Warning)
        LEVEL(Error)
    #undef LEVEL
    }

    return "Unknown";
}

// This function is a little janky looking...
static inline void TrimPath(std::string& Path)
{
    // _FULL_SOURCE_PATH is a compiler definition
    const char* FullPath = _FULL_SOURCE_PATH;
    const int FullPathSize = sizeof(_FULL_SOURCE_PATH);

    Path.erase(Path.find(FullPath), FullPathSize);
}

void Luna::Log::_LogImplementation(ELogLevel Level,
                                   std::string&& File,
                                   std::string&& Function,
                                   const unsigned int Line,
                                   const std::string&& Message)
{
    // This function feels a little expensive
    // TODO: Optimize this function?

    TrimPath(File);

    const std::string&& LevelString = GetLevelString(Level);

    // File:Line Function Level Message
    const char* FormatString = "{}:{} {} [{}] {}";
    const auto Args = std::make_format_args(File,
                                            Line,
                                            Function,
                                            LevelString,
                                            Message);
    const std::string Text = std::vformat(FormatString, Args);

    std::cout << Text << std::endl;
}
