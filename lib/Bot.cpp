#include <cmath>
#include <memory>

#include "../include/Bot.h"
#include "../include/TicTacToe.h"
#include "../include/utils.h"

Bot::Bot(char mark) : Player(mark), place_delay(1'500), accuracy(50.0f){};
Bot::Bot(char mark, int place_delay)
    : Player(mark), place_delay(place_delay), accuracy(50.0f){};

Bot::Bot(char mark, int place_delay, float accuracy)
    : Player(mark), place_delay(place_delay), accuracy(accuracy){};

int Bot::get_place_delay() const { return place_delay; }
int Bot::get_accuracy() const { return accuracy; }

int Bot::decide_position(TicTacToe &game) {
  int grid_size = game.get_grid_size(), square = std::pow(grid_size, 2);

  // If the random number is above the accuracy, create a random decision
  if (random() * 100.0 > accuracy) {
    std::vector<Cell> empty_cells = game.get_empty_cells();
    Cell random_cell = random_element(empty_cells);

    return (random_cell.position[0] * 3) + (random_cell.position[1] + 1);
  }

  int turn = game.get_turn(std::make_unique<Player>(*this)),
      opp_turn = opposing_turn(turn);

  Orientation self_optimal = game.optimal_orientation(turn);
  Orientation opp_optimal = game.optimal_orientation(opp_turn);

  int pos, self_req = game.required_moves(self_optimal, turn),
           opp_req = game.required_moves(opp_optimal, opp_turn);

  // If the required moves of the bot's and opponent's optimal orientation is
  // the same as the grid size (no optimal orientation), pick from one of the
  // best initial places
  if (opp_req == grid_size && self_req == grid_size) {
    Board &board = game.get_board();
    int center = game.get_board_center();

    // If the center is vacant, place the mark
    if (!game.has_mark(center))
      return center;

    // Otherwise, pick a corner
    std::vector<Cell> corners(4);
    std::vector<int> positions = {1, grid_size, (square - grid_size) + 1,
                                  square};

    int av_corners = 0;
    for (int &pos : positions) {
      if (!game.has_mark(pos))
        corners[av_corners++] = game.get_cell(pos);
    }

    corners.resize(av_corners);

    if (av_corners) {
      Cell corner = random_element(corners);

      return (corner.position[0] * 3) + (corner.position[1] + 1);
    } else {
      std::vector<Cell> empty_cells = game.get_empty_cells();
      Cell r_cell = random_element(empty_cells);

      return (r_cell.position[0] * 3) + (r_cell.position[1] + 1);
    }
  }

  // If the required moves of the bot itself is less than the required moves of
  // the player, proceed to playing offensively
  else if (self_req <= opp_req) {
    for (Cell &cell : self_optimal) {
      if (cell.mark == game.get_players()[turn - 1]->get_mark())
        continue;

      return (cell.position[0] * 3) + (cell.position[1] + 1);
    }
  }

  // Otherwise, play defensively to keep the player from winning
  else {
    for (Cell &cell : opp_optimal) {
      if (cell.mark == game.get_players()[opp_turn - 1]->get_mark())
        continue;

      return (cell.position[0] * 3) + (cell.position[1] + 1);
    }
  }

  return pos;
}

void Bot::play(TicTacToe &game) {
  Board &board = game.get_board();

  int pos = decide_position(game), grid_size = game.get_grid_size(),
      i = (pos - 1) / grid_size, j = (pos - 1) % grid_size;

  board[i][j].mark = mark;
  game.empty_slots--;

  // Map the board and process the played turn
  game.map_board();
  game.process();
}