#include <random>
#include <vector>

double random();

int opposing_turn(int turn);

template <typename T> T &random_element(std::vector<T> &vec) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> int_dist(0, vec.size());

  return vec[int_dist(gen)];
}
