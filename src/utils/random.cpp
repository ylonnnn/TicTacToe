#include "utils/random.hpp"

namespace utils::random
{
    double generate()
    {
        static std::random_device dg_rd;
        static std::mt19937 gen(dg_rd());

        std::uniform_real_distribution<> dist(0.0, 1.0);

        return dist(gen);
    }

} // namespace utils::random
