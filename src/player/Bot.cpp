#include <chrono>
#include <cmath>
#include <memory>
#include <thread>

#include "player/Bot.hpp"

namespace TicTacToe
{
    Bot::Bot(char mark) : Player(mark), place_delay_(1'500), accuracy_(50.0) {};
    Bot::Bot(char mark, uint32_t place_delay)
        : Player(mark), place_delay_(place_delay), accuracy_(50.0) {};

    Bot::Bot(char mark, uint32_t place_delay, double accuracy)
        : Player(mark), place_delay_(place_delay), accuracy_(accuracy) {};

    uint32_t Bot::place_delay() const { return place_delay_; }

    double Bot::accuracy() const { return accuracy_; }

    size_t Bot::decide_position(TicTacToe &game)
    {
        // TODO: Bot::decide_position()
        return 0;
    }

    void Bot::play(TicTacToe &game)
    {
        // TODO: Bot::play()
    }

    // int Bot::decide_position(TicTacToe &game) {
    //   int grid_size = game.get_grid_size(), square = std::pow(grid_size, 2);

    //   // If the random number is above the accuracy, create a random decision
    //   if (random() * 100.0 > accuracy) {
    //     std::vector<Cell> empty_cells = game.get_empty_cells();
    //     Cell &random_cell = random_element(empty_cells);

    //     return (random_cell.position[0] * grid_size) +
    //            (random_cell.position[1] + 1);
    //   }

    //   int turn = get_turn(game), opp_turn = opposing_turn(turn);

    //   Orientation self_optimal = game.optimal_orientation(turn);
    //   Orientation opp_optimal = game.optimal_orientation(opp_turn);

    //   int pos, self_req = game.required_moves(self_optimal, turn),
    //            opp_req = game.required_moves(opp_optimal, opp_turn);

    //   // If the required moves of the bot's and opponent's optimal
    //   orientation is
    //   // the same as the grid size (no optimal orientation), pick from one of
    //   the
    //   // best initial places
    //   if (opp_req == grid_size && self_req == grid_size) {
    //     Board &board = game.get_board();
    //     int center = game.get_board_center();

    //     // If the center is vacant, place the mark
    //     if (!game.has_mark(center))
    //       return center;

    //     // Otherwise, pick a corner
    //     std::vector<Cell> corners(4);
    //     std::vector<int> positions = {1, grid_size, (square - grid_size) + 1,
    //                                   square};

    //     int av_corners = 0;
    //     for (int &pos : positions) {
    //       if (!game.has_mark(pos))
    //         corners[av_corners++] = game.get_cell(pos);
    //     }

    //     corners.resize(av_corners);

    //     if (av_corners) {
    //       Cell &corner = random_element(corners);

    //       return (corner.position[0] * grid_size) + (corner.position[1] + 1);
    //     } else {
    //       std::vector<Cell> empty_cells = game.get_empty_cells();
    //       Cell &r_cell = random_element(empty_cells);

    //       return (r_cell.position[0] * grid_size) + (r_cell.position[1] + 1);
    //     }
    //   }

    //   // If the required moves of the bot itself is less than the required
    //   moves of
    //   // the player, proceed to playing offensively
    //   else if (self_req <= opp_req) {
    //     for (Cell &cell : self_optimal) {
    //       if (cell.mark == game.get_players()[turn - 1]->get_mark())
    //         continue;

    //       return (cell.position[0] * grid_size) + (cell.position[1] + 1);
    //     }
    //   }

    //   // Otherwise, play defensively to keep the player from winning
    //   else {
    //     for (Cell &cell : opp_optimal) {
    //       if (cell.mark == game.get_players()[opp_turn - 1]->get_mark())
    //         continue;

    //       return (cell.position[0] * grid_size) + (cell.position[1] + 1);
    //     }
    //   }

    //   return pos;
    // }

    // void Bot::play(TicTacToe &game) {
    //   int pos = decide_position(game);

    //   std::this_thread::sleep_for(std::chrono::milliseconds(place_delay));

    //   game.place_mark(get_turn(game), pos);

    //   // Map the board and process the played turn
    //   game.map_board();
    //   game.process();
    // }
} // namespace TicTacToe
