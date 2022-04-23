#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
  std::string word = argv[1];

  for (unsigned j = 0; j < word.length(); j++) {
    word[j] = std::tolower(word[j]);
  }

  bool valid = CheckValid(word);
  if (!valid) {
    std::cout << word << " contains a character not a part of the Hawaiian language." << std::endl;
    return 1;
  }

  std::string phonetics;
  phonetics = Transform(word);
  std::cout << phonetics << std::endl;
}