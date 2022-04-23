#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <vector>

// Your function declarations should go in this header file.

bool CheckValid(std::string word);

std::string Transform(std::string word);

std::string TransformO(std::string word, unsigned index);
std::string TransformU(std::string word, unsigned index);
std::string TransformI(std::string word, unsigned index);
std::string TransformE(std::string word, unsigned index);
std::string TransformA(std::string word, unsigned index);
std::string TransformW(std::string word, unsigned index);

#endif