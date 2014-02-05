#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> Split(const std::string &s, const char &delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while(std::getline(ss,token,delimiter)){
        if(!token.empty()){
            tokens.push_back(token);
        }
    }
    return tokens;
}

#endif // UTILS_H
