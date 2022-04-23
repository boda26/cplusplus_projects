#include "color.hpp"
#include <stdexcept>

const int kMax = 255;

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  if (red_ < 0 || red_ > kMax || green_ < 0 || green_ > kMax || blue_ < 0 || blue_ > kMax) {
    throw std::invalid_argument("color out of range!");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}