#include <iostream>
#include <cmath>
#include "other.hpp"

void showPoint(Point &p) {
  std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
}

double getLength(Point &p) {
  return sqrt(p.x * p.x + p.y * p.y);
}