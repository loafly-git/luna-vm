#include <iostream>
#include <string>

#include "JavaArgumentParser.h"

using namespace Luna;

int main(int argc, char* argv[])
{

    if(argc <= 1)
    {
        std::cerr << "No arguments specified." << std::endl;
        return 1;
    }

    return 0;
}
