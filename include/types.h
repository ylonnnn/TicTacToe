#include <ostream>
#include <vector>

struct Cell {
  char mark;
  int position[2]; // [row][col]
};

using Board = std::vector<std::vector<Cell>>;
using Orientation = std::vector<Cell>;

std::ostream &operator<<(std::ostream &os, const Cell &cell);

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
  os << "{ ";

  int vSize = vec.size();

  for (int i = 0; i < vSize; i++) {
    T el = vec[i];

    os << el << (i < (vSize - 1) ? ", " : "");
  }

  return os << " }";
}