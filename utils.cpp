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
    int index = s.find_last_of(folder_separator);
    if(index==std::string::npos){
        return "";
    }
    std::string path = s.substr(0,index+1);
    return path;
}
