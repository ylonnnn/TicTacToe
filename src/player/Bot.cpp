#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>

#include "player/Bot.hpp"
#include "tictactoe/TicTacToe.hpp"
#include "utils/random.hpp"

namespace TicTacToe
{
    Bot::Bot(char mark) : Player(mark), place_delay_(1'500), accuracy_(50.0) {};
    Bot::Bot(char mark, uint32_t place_delay)
        : Player(mark), place_delay_(place_delay), accuracy_(50.0) {};

    Bot::Bot(char mark, uint32_t place_delay, double accuracy)
        : Player(mark), place_delay_(place_delay), accuracy_(accuracy) {};

    uint32_t Bot::place_delay() const { return place_delay_; }

    double Bot::accuracy() const { return accuracy_; }

    uint32_t Bot::decide_position(TicTacToe &game)
    {
        uint32_t grid_size = game.grid_size(), square = std::pow(grid_size, 2);

        // If the random number is above the accuracy, create a random decision

        if ((utils::random::generate() * 100.0) > accuracy_)
        {
            std::vector<Cell *> empty_cells = game.empty_cells();
            return utils::random::random_element(empty_cells)->absolute_pos();
        }

        // Retrieve self and opposing turn
        Turn *self = game.turn(*this), *opp = game.turn(game.opposing_turn());

        Orientation self_optimal = game.optimal_orientation(*self);
        Orientation opp_optimal = game.optimal_orientation(*opp);

        uint32_t pos, self_req = self_optimal.required_moves(),
                      opp_req = opp_optimal.required_moves();

        // If the required moves of the bot's and opponent's optimal orientation
        // is the same as the grid size (no optimal orientation), pick from one
        // of the best initial places
        if (opp_req == grid_size && self_req == grid_size)
        {
            uint32_t center = game.board_center();
            Cell &c_cell = game.cell_at(center);

            // If the center is vacant, place the mark
            if (!c_cell.marked())
                return center;

            // Otherwise, pick a corner
            std::vector<Cell *> corners(4);
            std::vector<uint32_t> positions = {
                1, grid_size, (square - grid_size) + 1, square};

            uint32_t av_corners = 0;
            for (uint32_t &pos : positions)
            {
                Cell &cell = game.cell_at(pos);

                if (!cell.marked())
                    corners[av_corners++] = &cell;
            }

            corners.resize(av_corners);

            // There are available corners to be filled
            if (av_corners)
                return utils::random::random_element(corners)->absolute_pos();

            else
            {
                std::vector<Cell *> empty_cells = game.empty_cells();
                return utils::random::random_element(empty_cells)
                    ->absolute_pos();
            }
        }

        // If the required moves of the bot itself is less than the required
        // moves of the player, proceed to playing offensively
        else if (self_req <= opp_req)
        {
            for (Cell *cell : self_optimal.cells)
                if (cell->mark() != mark_)
                    return cell->absolute_pos();
        }

        // Otherwise, play defensively to keep the opponent from winning
        else
        {
            for (Cell *cell : opp_optimal.cells)
                if (cell->mark() != opp->player().mark())
                    return cell->absolute_pos();
        }

        return pos;
    }

    void Bot::play(TicTacToe &game)
    {
        uint32_t pos = decide_position(game);

        // Apply place delay
        std::this_thread::sleep_for(std::chrono::milliseconds(place_delay_));

        Turn *self = game.turn(*this);

        // Highly unlikely, impossible even
        if (self == nullptr)
            return;

        game.cell_at(pos).place(*self);

        // Map the board and process the played turn
        game.map_board();
        game.process();
    }

} // namespace TicTacToe
