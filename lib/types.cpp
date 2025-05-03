
#include <ostream>

#include "../include/types.h"

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
  return os << cell.mark << " <" << cell.position[0] << ", " << cell.position[1]
            << ">";
}
