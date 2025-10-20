#pragma once

#include <cstddef>
#include <cstdint>

#include "player/Player.hpp"

namespace TicTacToe
{
    class Bot : public Player
    {
      public:
        Bot(char mark);
        Bot(char mark, uint32_t place_delay);
        Bot(char mark, uint32_t place_delay, double accuracy);

        uint32_t place_delay() const;
        double accuracy() const;

        uint32_t decide_position(TicTacToe &game);

        void play(TicTacToe &game) override;

      private:
        uint32_t place_delay_;
        double accuracy_;
    };

} // namespace TicTacToe
