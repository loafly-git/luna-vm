#include "Log.h"

#include <format>
#include <iostream>
#include <string>
#include <string_view>

using namespace Luna;

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
}

// This function is a little janky looking...
static inline void TrimPath(std::string& Path)
{
    // _FULL_SOURCE_PATH is a compiler definition
    const char* FullPath = _FULL_SOURCE_PATH;
    const int FullPathSize = sizeof(_FULL_SOURCE_PATH);

    Path.erase(Path.find(FullPath), FullPathSize);
}

void Luna::_LogImplementation(ELogLevel Level,
                              std::string&& File,
                              const unsigned int Line,
                              const std::string&& Message
)
{
    // This function feels a little expensive
    // TODO: Optimize this function?

    const std::string&& LevelString = GetLevelString(Level);

    TrimPath(File);

    // File:Line Level Message
    const char* FormatString = "{}:{} [{}] {}";
    const auto Args = std::make_format_args(File,
                                            Line,
                                            LevelString,
                                            Message);
    const std::string Text = std::vformat(FormatString, Args);

    std::cout << Text << std::endl;
}
