#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include "tictactoe/Turn.hpp"

namespace TicTacToe
{
    class Cell
    {
      public:
        Cell(uint32_t absolute_pos, std::array<uint32_t, 2> &&pos);

        const std::array<uint32_t, 2> position() const;

        char mark() const;

        bool marked() const;
        bool place(Turn *turn);

      private:
        Turn *turn_ = nullptr;
        uint32_t absolute_pos_;
        std::array<uint32_t, 2> pos_;
    };

    struct Orientation
    {
        Turn &turn;
        std::vector<Cell *> cells;

        Orientation(Turn &turn);

        // uint32_t count_required_moves() const { for (const Cell *cell :
        // cells) }
    };

} // namespace TicTacToe
