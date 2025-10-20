#pragma once

#include "player/Player.hpp"
#include "tictactoe/TicTacToe.hpp"

namespace TicTacToe
{
    Player::Player(char mark) : mark_(mark) {}

    char Player::mark() const { return mark_; }

    void Player::play(TicTacToe &game)
    {
        // TODO: Player::play()
    }

} // namespace TicTacToe

// namespace TicTacToe

// #include <cmath>

// #include <iostream>

// #include "../include/TicTacToe.h"
// #include "../include/utils.h"

// Player::Player(char mark) : mark(mark) {};

// char Player::get_mark() const { return mark; }

// int Player::get_turn(TicTacToe &game) const { return game.get_turn(this); }

// void Player::play(TicTacToe &game)
// {
//     Board &board = game.get_board();
//     int pos, turn = game.get_turn(this);

//     std::cout << "[" << turn << "] Enter the Mark Position [" << mark << "]:
//     "; std::cin >> pos;

//     int grid_size = game.get_grid_size(), max_pos = std::pow(grid_size, 2);

//     if (pos < 1 || pos > max_pos || std::cin.fail())
//     {
//         std::cout << "Invalid position! Valid positions range from 1 to "
//                   << max_pos << "\n";

//         return play(game);
//     }

//     // If one of the players' marks are in that cell, it has already been
//     marked if (game.has_mark(pos))
//     {
//         std::cout << "This position is already marked!\n";

//         return play(game);
//     }

//     game.place_mark(turn, pos);

//     // Map the board and process the played turn
//     game.map_board();
//     game.process();
// }
