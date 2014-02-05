#include "utils.h"

#ifdef WIN32
std::string folder_separator = "\";
#else
std::string folder_separator =  "/";
#endif

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


std::string GetFilePath(const std::string &s)
{
    std::vector<std::string> tokens = Split(s, folder_separator.at(0) );
    tokens.pop_back();
    std::string path;
    for(std::vector<std::string>::iterator it = tokens.begin();
        it != tokens.end();
        it++){
        path.append((*it));
        path.append(folder_separator.c_str());
    }
    return path;
}
