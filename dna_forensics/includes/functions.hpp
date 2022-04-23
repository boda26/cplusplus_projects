#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
#include <map>
#include <vector>

std::map<std::string, std::vector<int>> ReadFile(const std::string& filename);

std::vector<std::string> GetStr(const std::string& filename);

int FindLongestConsecutiveRun(const std::string& input, const std::string& key);

#endif