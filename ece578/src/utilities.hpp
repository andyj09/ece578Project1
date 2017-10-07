#include <iostream>

struct debugInfo_t {
    std::string fnameA;
    std::string fnameB;
    bool enabled;
    debugInfo_t() : fnameA(""),fnameB(""), enabled(false) {};
};

bool getCLIArgs(int argc, const char *argv[], debugInfo_t &dInfo)
{
    // do nothing if no arguments are passed in
    if ( argc == 2)
    {
        std::string arg = argv[1];
        if (arg == "-h" || arg == "--help")
        {
            std::cout << "usage: " << argv[0] << " [ -debug ";
            std::cout << "[fnameA filename] "; 
            std::cout << "[fnameB filename] ]" << std::endl;
        }
        return false;
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
            else if (arg == "-fnameB")
            {
                index += 1;
                dInfo.fnameB = std::string(argv[index]);
            }
            else if (arg == "-d")
            {
                dInfo.enabled = true;
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