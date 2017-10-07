#ifndef PROBUTILS_HPP
#define PROBUTILS_HPP

#include <random>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// generic function to generate a uniform distribution
// between lower and upper bounds
template <typename T>
static void genUniformDist(std::vector<T> &vec, int cnt, int lower=0, int upper=1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(lower,upper);

    for (int i=0; i < cnt; i++)
    {
        vec.emplace_back(dist(gen));
    }
}

// Inverse CDF transformation function
template<typename T>
static T iCDFfunc(T u, T lambda)
{
    T out = (-1/lambda) * std::log(1-u);
    return out;
}

// generic function to compute exponentially distributed 
// values with mean lambda  
template<typename T>
static void genExpDist(std::vector<T> &inVec, std::vector<T> &outVec, T lambda)
{
    for ( int i=0; i < inVec.size(); i++ )
    {
       outVec.emplace_back(iCDFfunc(inVec[i], lambda));
    }
}

template<typename T>
static void genPoissonDistTraffic(std::vector<T> &outVec, double lambda, double duration)
{
    int lower_bound = 0;
    int upper_bound = 1;
    double sum = 0.0;
    double x = 0.0;
    double exp = 0.0; 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(lower_bound,upper_bound);

    while ( sum < duration )
    {
        // uniformly distributed number
        x = dist(gen);
        // exponentially distributed number
        exp = iCDFfunc(x, lambda);
        // append new number to vector only if duration has not been met
        if ( (sum+exp) > duration )
            break;
        outVec.push_back(exp);
        // increment counter
        sum += exp;
    }
}

template <typename T>
static bool verifyPoissonTraffic(std::vector<T> &traffic, T duration)
{
    T sum = 0.0;
    for (const auto &time : traffic )
    {
        sum += time;
    }
    
    return ( sum < duration );
}

static void split(const std::string &s, char delim, std::vector<double> &elems) {
    std::stringstream ss(s);
    std::string item;
    double num;
    while (std::getline(ss, item, delim)) {
        num = std::stod(item, nullptr);
        elems.emplace_back(num);
    }
}

static inline void splitStrToDouble(const std::string &s, char delim, std::vector<double> &outVec)
{
    split(s, delim, outVec);
}

template<typename T>
static void writeValuesToFile(std::vector<T> vec, double lambda, std::string fName)
{
    std::ofstream outFile;
    outFile.open (fName);
    double sum = 0.0;
    outFile << lambda << "\n";
    outFile << vec.size() << "\n";
    for ( const auto &val : vec )
    {
        outFile << val << ",";
        sum += val;
    }
    outFile << "\n";
    outFile << sum;
    outFile.close();
}

static void readValuesFromFile(std::vector<double> &outVec, std::string fName)
{
    std::ifstream inFile(fName);
    std::string line;
    double value;
    int size;
    if (inFile.is_open())
    {
        // read lambda value
        getline(inFile, line);
        value = std::stod(line,nullptr);

        // read total number of elements
        getline(inFile, line);
        size = std::stoi(line, nullptr);

        // read all values
        getline(inFile, line);
        splitStrToDouble(line, ',', outVec);

        inFile.close();
    }
}
    
#endif // PROBUTILS_HPP