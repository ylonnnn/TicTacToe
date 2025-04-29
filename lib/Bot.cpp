#include "../include/Bot.h"
#include "../include/TicTacToe.h"
#include "../include/utils.h"

#include <cmath>
#include <memory>

Bot::Bot(char mark) : Player(mark), place_delay(1'500), accuracy(50.0f){};
Bot::Bot(char mark, int place_delay)
    : Player(mark), place_delay(place_delay), accuracy(50.0f){};

Bot::Bot(char mark, int place_delay, float accuracy)
    : Player(mark), place_delay(place_delay), accuracy(accuracy){};

int Bot::get_place_delay() const { return place_delay; }
int Bot::get_accuracy() const { return accuracy; }

int Bot::decide_position(TicTacToe &game) {
  // If the random number is above the accuracy, create a random decision
  if (random() * 100.0 > accuracy) {
    int initial = std::round(random() * 9.0);

    while (initial < 1 || initial > 9 || game.has_mark(initial))
      initial = std::round(random() * 9.0);

    return initial;
  }

  int turn = game.get_turn(std::make_unique<Player>(*this)),
      opp_turn = opposing_turn(turn);

  Orientation self_optimal = game.optimal_orientation(turn);
  Orientation opp_optimal = game.optimal_orientation(opp_turn);

  int pos, self_req = game.required_moves(self_optimal, turn),
           opp_req = game.required_moves(opp_optimal, opp_turn);

  // If the required moves of the bot itself is less than the required moves of
  // the player, proceed to playing offensively
  if (self_req < opp_req) {
    for (Cell &cell : self_optimal) {
      if (cell.mark == game.get_players()[turn - 1]->get_mark())
        continue;

      pos = (cell.position[0] * 3) + (cell.position[1] + 1);

      break;
    }
  }

  // Otherwise, play defensively to keep the player from winning
  else {
    for (Cell &cell : opp_optimal) {
      if (cell.mark == game.get_players()[opp_turn - 1]->get_mark())
        continue;

      pos = (cell.position[0] * 3) + (cell.position[1] + 1);

      break;
    }
  }

  return pos;
}

void Bot::play(TicTacToe &game) {
  // TODO: Bot play()
  Board &board = game.get_board();

  int pos = decide_position(game),
      turn = game.get_turn(std::make_unique<Player>(*this)),
      grid_size = game.get_grid_size(), i = (pos - 1) / grid_size,
      j = (pos - 1) % grid_size;

  board[i][j].mark = mark;
  game.empty_slots--;

  // Map the board and process the played turn
  game.map_board();
  game.process();
}