#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width,size_t height) {
  width_ = width;height_ = height;max_ele_ = INT32_MIN;min_ele_ = INT32_MAX;std::ifstream ifs{filename};std::string line;
  while (std::getline(ifs, line)) {std::vector<int> vec;vec.clear();std::string word;
    for (auto c : line) {
      if (c == ' ') {
        if (!word.empty()) {
          if (word[0] == '-') {
            int num = -1 * std::stoi(word.substr(1));
            if (num > max_ele_) {max_ele_ = num;}
            if (num < min_ele_) {min_ele_ = num;}vec.push_back(num);word = "";
          } else {
            int num = std::stoi(word);
            if (num > max_ele_) {max_ele_ = num;}
            if (num < min_ele_) {min_ele_ = num;}vec.push_back(num);word = "";
          }
        }
      } else {word += c;}
    }
    if (!word.empty()) {
      if (word[0] == '-') {
        int num = -1 * std::stoi(word.substr(1));
        if (num > max_ele_) {max_ele_ = num;}
        if (num < min_ele_) {min_ele_ = num;}vec.push_back(num);word = "";
      } else {
        int num = std::stoi(word);
        if (num > max_ele_) {max_ele_ = num;}
        if (num < min_ele_) {min_ele_ = num;}
        vec.push_back(num);
        word = "";
      }
    }
    if (!vec.empty()) {
        data_.push_back(vec);
    }
  }
  if (width_ != data_.at(0).size() || height_ != data_.size()) {
    throw std::runtime_error("");
  }
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_[row][col];
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}
