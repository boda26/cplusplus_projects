#include "functions.hpp"
#include "utilities.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

std::map<std::string, std::vector<int>> ReadFile(const std::string& filename) {
    std::map<std::string, std::vector<int>> infomap;
    std::ifstream ifs{filename};
    int i = 0;
    for(std::string line; std::getline(ifs, line); line = "") {
        //std::cout << "line = \"" << line << '\"' << std::endl;
        if (i != 0) {
            std::vector<std::string> linevector = utilities::GetSubstrs(line, ',');
            std::string name = linevector.at(0);
            int str1 = std::stoi(linevector.at(1));
            int str2 = std::stoi(linevector.at(2));
            int str3 = std::stoi(linevector.at(3));
            std::vector<int> strs = {str1, str2, str3};
            infomap.insert(std::pair<std::string, std::vector<int>>(name, strs));
        }
        i++;
    }
    return infomap;
}

std::vector<std::string> GetStr(const std::string& filename) {
    std::vector<std::string> strvector;
    std::ifstream ifs{filename};
    int i = 0;
    for(std::string line; std::getline(ifs, line); line = "") {
        if (i == 0) {
            std::vector<std::string> linevector = utilities::GetSubstrs(line, ',');
            std::string str1 = linevector.at(1);
            std::string str2 = linevector.at(2);
            std::string str3 = linevector.at(3);
            strvector = {str1, str2, str3};
            break;
        }
    }
    return strvector;
}

int FindLongestConsecutiveRun(const std::string& input, const std::string& key) {
    int len = key.length();
    int maxcount = 0;
    int count = 0;
    unsigned i = 0;
    while (i < input.length()) {
        //std::cout << i <<std::endl;
        if (i + len > input.length()) {
            break;
        }
        std::string str = input.substr(i, len);
        //std::cout << str << std::endl;
        if (str == key) {
            count++;
            i += len;
        } else {
            if (count > maxcount) {
                maxcount = count;
            }
            count = 0;
            i++;
        }
    }
    //std::cout << count << std::endl;
    if (count > maxcount) {
        maxcount = count;
    }
    return maxcount;
}