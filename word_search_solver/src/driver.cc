#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"
#include "WordLocation.hpp"
#include "CharPositions.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'a', 'c', 'h', 'l', 'h'},
                                        {'e', 'a', 'a', 'h', 'e'},
                                        {'l', 's', 'e', 'h', 'l'},
                                        {'p', 'b', 't', 'o', 'l'},
                                        {'o', 'e', 't', 'l', 'o'}};
  WordSearchSolver wss(puzzle);
  std::cout << wss.FindWord("he", CheckDirection::kLeftDiag);
  //std::cout << wss.FindWord("hello");

}