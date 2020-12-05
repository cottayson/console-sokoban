#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <iostream>

bool g_wide = true;

template<typename T>
void showVector(std::vector<T>& v) {
  for (auto elem : v) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

#endif