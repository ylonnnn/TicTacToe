#include "../include/TicTacToe.h"
#include "../include/utils.h"

#include <array>
#include <cmath>
#include <iostream>
#include <memory>

TicTacToe::TicTacToe(const int &grid_size, std::array<Player, 2> players)
    : grid_size(grid_size), players(players) {
  initialize_turn();
  initialize_board();
}

void TicTacToe::initialize_turn() { turn = std::round(random() + 1); }

void TicTacToe::initialize_board() {
  board = new char *[grid_size];

  for (int i = 0; i < grid_size; i++) {
    board[i] = new char[grid_size];

    for (int j = 0; j < grid_size; j++) {
      board[i][j] = '_';
    }
  }
}

int TicTacToe::get_turn() { return turn; }

void TicTacToe::map_board() {
  for (int i = 0; i < grid_size; i++) {
    for (int j = 0; j < grid_size; j++) {
      std::cout << board[i][j] << '\t';

      if (j < grid_size - 1)
        std::cout << "|\t";
    }

    std::cout << "\n";
  }
}

void TicTacToe::pos_prompt() {
  Player player = players[turn - 1];

  char mark = player.get_mark();
  int pos, opp_turn = opposing_turn(turn);

  std::cout << "[" << turn << "] Enter the Mark Position [" << mark << "]: ";
  std::cin >> pos;

  if (pos < 1 || pos > 9 || std::cin.fail()) {
    std::cout << "Invalid position! Valid positions range from 1 to 9\n";

    return pos_prompt();
  }

  int i = (pos - 1) / grid_size, j = (pos - 1) % grid_size;
  char existing_mark = board[i][j];

  // If one of the players' marks are in that cell, it has already been marked
  if (existing_mark == mark ||
      existing_mark == players[opp_turn - 1].get_mark()) {
    std::cout << "This position is already marked!\n";

    return pos_prompt();
  }

  board[i][j] = mark;

  // Check if a player has won
  check(turn);

  turn = opp_turn;

  map_board();
}

void TicTacToe::check(int turn) {
  Player player = players[turn - 1];

  char mark = player.get_mark();

  char **horizontal = horizontal_orientations(turn);
  char **vertical = vertical_orientations(turn);
  char **diagonal = diagonal_orientations(turn);

  // Horizontal Check
  for (int i = 0; i < grid_size; i++) {
    char *orientation = horizontal[i];
    if (orientation == nullptr)
      continue;

    for (int j = 0; j <= grid_size; j++) {
      char cell_mark = orientation[j];

      // Every cell matched the mark of the player
      if (j == grid_size) {
        winner = std::make_unique<Player>(player);
      }

      if (cell_mark != mark)
        break;
    }
  }

  // Vertical Check
  for (int i = 0; i < grid_size; i++) {
    char *orientation = vertical[i];
    if (orientation == nullptr)
      continue;

    for (int j = 0; j <= grid_size; j++) {
      char cell_mark = orientation[j];

      // Every cell matched the mark of the player
      if (j == grid_size) {
        winner = std::make_unique<Player>(player);
      }

      if (cell_mark != mark)
        break;
    }
  }

  // Diagonal Check
  for (int i = 0; i < 2; i++) {
    char *orientation = diagonal[i];
    if (orientation == nullptr)
      continue;

    for (int j = 0; j <= grid_size; j++) {
      char cell_mark = orientation[j];

      // Every cell matched the mark of the player
      if (j == grid_size) {
        winner = std::make_unique<Player>(player);
      }

      if (cell_mark != mark)
        break;
    }
  }
}

char **TicTacToe::horizontal_orientations(int turn) {
  Player opponent = players[opposing_turn(turn) - 1];
  char opponent_mark = opponent.get_mark();

  char **orientations = new char *[grid_size];

  for (int i = 0; i < grid_size; i++) {
    // orientations[i] = new char[grid_size];

    char *orientation = new char[grid_size];

    for (int j = 0; j < grid_size; j++) {
      char cell_mark = board[i][j];

      if (cell_mark != opponent_mark)
        orientation[j] = cell_mark;

      else {
        orientation = nullptr;

        break;
      }
    }

    orientations[i] = orientation;
  }

  return orientations;
}

char **TicTacToe::vertical_orientations(int turn) {
  Player opponent = players[opposing_turn(turn) - 1];
  char opponent_mark = opponent.get_mark();

  char **orientations = new char *[grid_size];

  for (int i = 0; i < grid_size; i++) {

    char *orientation = new char[grid_size];

    for (int j = 0; j < grid_size; j++) {
      char cell_mark = board[j][i];

      if (cell_mark != opponent_mark)
        orientation[j] = cell_mark;

      else {
        orientation = nullptr;

        break;
      }
    }

    orientations[i] = orientation;
  }

  return orientations;
}

char **TicTacToe::diagonal_orientations(int turn) {
  Player opponent = players[opposing_turn(turn) - 1];

  const int do_n = 2;

  char opponent_mark = opponent.get_mark(), **orientations = new char *[do_n] {
    new char[grid_size], new char[grid_size]
  };

  bool valid[do_n] = {true, true};

  for (int i = 0; i < grid_size; i++) {

    // Diagonal
    // [i][i]
    {

      char cell_mark = board[i][i];

      if (cell_mark != opponent_mark)
        orientations[0][i] = cell_mark;

      else
        valid[0] = false;
    }

    // Anti-Diagonal
    // [i][grid_size - (i + 1)]
    {

      char cell_mark = board[i][grid_size - (i + 1)];

      if (cell_mark != opponent_mark)
        orientations[1][i] = cell_mark;

      else
        valid[1] = false;
    }
  }

  for (int i = 0; i < do_n; i++) {
    if (!valid[i])
      orientations[i] = nullptr;
  }

  return orientations;
}

void TicTacToe::start() {
  // TODO: TicTacToe Start

  // int pos;
  while (winner == nullptr) {
    pos_prompt();
  }

  std::cout << "WINNER: Player " << winner->get_mark() << "\n";

  // std::cout << "Enter the Mark Position ["<< << "]: ";
}

void TicTacToe::end() {
  // TODO: TicTacToe End
}