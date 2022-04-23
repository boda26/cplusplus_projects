#include "WordSearchSolver.hpp"
#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include <string>
#include <vector>
#include <iostream>


bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle) {
  puzzle_ = puzzle;
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

WordLocation WordSearchSolver::FillWordLocation(const std::string& word, bool find, const std::vector<std::vector<unsigned>>& positions) const {
  WordLocation wordlocation;
  if (find) {
    wordlocation.word = word;
    wordlocation.char_positions = {};
    for (unsigned i = 0; i < word.length(); i++) {
      CharPositions charposition = {};
      charposition.character = word[i];
      charposition.row = positions[i][0];
      charposition.col = positions[i][1];
      wordlocation.char_positions.push_back(charposition);
    }
  }
  return wordlocation;
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation w1 = FindWord(word, CheckDirection::kHorizontal);
  if (!w1.word.empty()) {
    return w1;
  } 
  WordLocation w2 = FindWord(word, CheckDirection::kVertical);
  if (!w2.word.empty()) {
    return w2;
  }
  WordLocation w3 = FindWord(word, CheckDirection::kLeftDiag);
  if (!w3.word.empty()) {
    return w3;
  }
  WordLocation w4 = FindWord(word, CheckDirection::kRightDiag);
  return w4;
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
  bool find = false;
  std::vector<std::vector<unsigned>> positions;
  WordLocation wordloc;
  if (direction == CheckDirection::kHorizontal) {
    for (unsigned i = 0; i < puzzle_height_; i++) {
      unsigned check = 0;
      positions.clear();
      for (unsigned j = 0; j < puzzle_width_; j++) {
        if (puzzle_[i][j] == word[check]) {
          check++;
          std::vector<unsigned> pos = {i, j};
          positions.push_back(pos);
          if (check == word.length()) {
            find = true;wordloc = FillWordLocation(word, find, positions);
            break;
          } 
        } else {
          check = 0;
          positions.clear();
        }
      }
    }
  } else if (direction == CheckDirection::kVertical) {
    for (unsigned i = 0; i < puzzle_width_; i++) {
      unsigned check = 0;
      positions.clear();
      for (unsigned j = 0; j < puzzle_height_; j++) {
        if (puzzle_[j][i] == word.at(check)) {
          check++;
          std::vector<unsigned> pos = {j, i};
          positions.push_back(pos);
          if (check == word.length()) {
            find = true;
            wordloc = FillWordLocation(word, find, positions);
            break;
          }
        } else {
          check = 0;
          positions.clear();
          if (word[check] == puzzle_[j][i]) {
            check++;
            std::vector<unsigned> pos = {j, i};
            positions.push_back(pos);
          }
        }
      }
    }
  } else if (direction == CheckDirection::kLeftDiag) {
    unsigned maxsum = puzzle_height_ + puzzle_width_ - 2;
    for (unsigned sum = 0; sum <= maxsum; ++sum) {
      unsigned check = 0;
      positions.clear();
      for (unsigned i = 0; i < puzzle_height_; ++i) {
        for (unsigned j = 0; j < puzzle_width_; ++j) {
          if (i + j - sum == 0) {
            if (puzzle_[i][j] == word[check]) {
              check++;
              std::vector<unsigned> pos = {i, j};
              positions.push_back(pos);
              if (check == word.length()) {
                find = true;wordloc = FillWordLocation(word, find, positions);
                break;
              } 
            } else {
              check = 0;
              positions.clear();
              if (word[check] == puzzle_[i][j]) {
                check++;
                std::vector<unsigned> pos = {i,j};
                positions.push_back(pos);
              }
            } 
          }
        }
      }
    }
  } else if (direction == CheckDirection::kRightDiag) {
    int max = std::max((int)puzzle_height_, (int)puzzle_width_);
    int min = std::max(0 - (int)puzzle_height_, 0 - (int)puzzle_width_);
    for (int diff = max; diff >= min; diff--) {
      unsigned check = 0;
      positions.clear();
      for (int i = 0; i < (int)puzzle_height_; i++) {
        for (int j = 0; j < (int)puzzle_width_; j++) {
          if (i - j == diff) {
            if (puzzle_[i][j] == word[check]) {
              check++;
              std::vector<unsigned> pos = {(unsigned)i, (unsigned)j};
              positions.push_back(pos);
              if (check == word.length()) {
                find = true;
                wordloc = FillWordLocation(word, find, positions);
                break;
              } 
            } else {
              check = 0;
              positions.clear();
            } 
          }
        }
      }
    }
  }
  return wordloc;
}