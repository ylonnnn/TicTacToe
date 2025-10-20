#pragma once

#include "player/Player.hpp"
#include "tictactoe/TicTacToe.hpp"
#include <cmath>
#include <iostream>

namespace TicTacToe
{
    Player::Player(char mark) : mark_(mark) {}

    char Player::mark() const { return mark_; }

    void Player::play(TicTacToe &game)
    {
        Turn &turn = game.turn();
        uint32_t pos;

        std::cout << "Enter the Mark Position [" << mark_ << "]: ";
        std::cin >> pos;

        uint32_t grid_size = game.grid_size(), max_pos = std::pow(grid_size, 2);

        if (pos > max_pos || std::cin.fail())
        {
            std::cout << "Invalid position! Valid positions range from 1 to "
                      << max_pos << "\n";

            return play(game);
        }

        // If one of the players' marks are in that cell, it has already been
        // marked
        Cell &cell = game.cell_at(pos);
        if (cell.marked())
        {
            std::cout << "This position is already marked!\n";
            return play(game);
        }

        cell.place(turn);

        // Map the board and process the played turn
        game.map_board();
        game.process();
    }

} // namespace TicTacToe
