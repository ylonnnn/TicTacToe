#pragma once

#include <cstdint>
#include <memory>

#include "player/Player.hpp"

namespace TicTacToe
{
    class Turn
    {
      public:
        Turn(uint32_t no, std::unique_ptr<Player> &&player);

        uint32_t number() const;

        Player &player();
        const Player &player() const;

      private:
        uint32_t no_;
        std::unique_ptr<Player> player_;
    };

} // namespace TicTacToe
