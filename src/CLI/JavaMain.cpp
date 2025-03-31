#include <iostream>
#include <string>

#include "Log/Log.h"

int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        std::cerr << "No arguments specified." << std::endl;
        return 1;
    }

    LNLOGD("The meaning of life is {}", 42);

    return 0;
}
