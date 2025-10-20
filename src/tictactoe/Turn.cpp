#include "tictactoe/Turn.hpp"
#include "player/Player.hpp"

namespace TicTacToe
{
    Turn::Turn(uint32_t no, std::unique_ptr<Player> &&player)
        : no_(no), player_(std::move(player))
    {
    }

    uint32_t Turn::number() const { return no_; }

    Player &Turn::player() { return *player_; }

    const Player &Turn::player() const { return *player_; }

} // namespace TicTacToe
