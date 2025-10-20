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

        uint32_t absolute_pos() const;
        const std::array<uint32_t, 2> position() const;

        char mark() const;

        bool marked() const;
        bool place(Turn &turn);

      private:
        Turn *turn_ = nullptr;
        uint32_t absolute_pos_;
        std::array<uint32_t, 2> pos_;
    };

    struct Orientation
    {
        TicTacToe &game;
        Turn &turn;
        std::vector<Cell *> cells;

        Orientation(TicTacToe &game, Turn &turn);

        uint32_t required_moves() const;
    };

} // namespace TicTacToe
