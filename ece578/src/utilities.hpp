#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "debugInfo.hpp"
#include <iostream>
#include <string>

static bool getCLIArgs(int argc, const char *argv[], debugInfo_t &dInfo)
{
    if ( argc == 1)
    {
        std::cout << "ERROR: must pass at least one argument\n";
        return false;
    }
    // two arguments -h or config file
    if ( argc == 2)
    {
        std::string arg = argv[1];
        if (arg == "-h" || arg == "--help")
        {
            std::cout << "usage: " << argv[0] << " [ -debug ";
            std::cout << "[fnameA filename] "; 
            std::cout << "[fnameB filename] ]" << std::endl;
            return false;
        }
        else if (arg == "-config")
        {
            dInfo.config = std::string(argv[1]);
            return true;
        }
    }
    else
    {
        // grab each argument
        int index = 1;
        while ( index < argc )
        {
            std::string arg = argv[index];
            if (arg == "-fnameA")
            {
                index += 1;
                dInfo.fnameA = std::string(argv[index]);
            }
            else if (arg == "-fnameC")
            {
                index += 1;
                dInfo.fnameC = std::string(argv[index]);
            }
            else if (arg == "-config")
            {
                index += 1;
                dInfo.config = std::string(argv[index]);
            }
            else if (arg == "-debug")
            {
                dInfo.debugEnabled = true;
            }
            else {
                std::cout << "invalid argument, use -h for help\n";
                return false;
            }
            index += 1;
        }
    }
    return true;
}

#endif // UTILITIES_HPP