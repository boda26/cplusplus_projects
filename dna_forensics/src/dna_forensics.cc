#include <iostream>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::map<std::string, std::vector<int>> infomap = ReadFile(argv[1]);
  std::vector<std::string> strvector = GetStr(argv[1]);
  std::vector<int> countinput;
  for (unsigned i = 0; i < strvector.size(); i++) {
    int maxcount = FindLongestConsecutiveRun(argv[2], strvector.at(i));
    countinput.push_back(maxcount);
  }
  int boolvalue = 0;
  std::string name;
  for (auto it = infomap.begin(); it != infomap.end(); ++it) {
    std::vector<int> personvector = it->second;
    bool b = true;
    for (unsigned j = 0; j < countinput.size(); j++) {
      if (countinput.at(j) != personvector.at(j)) {
        b = false;
      }
    }
    if (b) {
      boolvalue++;
      name = it->first;
    }
  }
  if (boolvalue == 1) {
    std::cout << name << std::endl;
  } else {
    std::cout << "No match" << std::endl;
  }
  return 0;
}