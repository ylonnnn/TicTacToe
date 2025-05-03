#include <iostream>
#include <random>
#include <vector>

double random();

int opposing_turn(int turn);

template <typename T> T &random_element(std::vector<T> &vec) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> int_dist(0, vec.size() - 1);

  return vec[int_dist(gen)];
}
