#ifndef DEBUGINFO_HPP
#define DEBUGINFO_HPP

#include <string>

struct debugInfo_t {
    std::string fnameA;
    std::string fnameC;
    std::string config;
    bool debugEnabled;
    debugInfo_t() : fnameA(""),fnameC(""),config(""),debugEnabled(false) {};
};

#endif // DEBUGINFO_HPP