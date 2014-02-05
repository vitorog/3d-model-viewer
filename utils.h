#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> Split(const std::string &s, const char &delimiter);

//Removes a file name and returns the path
std::string GetFilePath(const std::string &s);

#endif // UTILS_H
