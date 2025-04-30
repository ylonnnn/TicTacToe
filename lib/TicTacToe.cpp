#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../include/TicTacToe.h"
#include "../include/utils.h"

TicTacToe::TicTacToe(int grid_size,
                     std::array<std::unique_ptr<Player>, 2> &players)
    : grid_size(grid_size), players(players), winner(nullptr) {
  initialize_turn();
  initialize_board();
}

void TicTacToe::initialize_turn() { turn = std::round(random() + 1); }

void TicTacToe::initialize_board() {
  // Initialize the empty slots as well
  empty_slots = std::pow(grid_size, 2);
  board = std::vector<std::vector<Cell>>(grid_size);

  for (int i = 0; i < grid_size; i++) {
    board[i] = std::vector<Cell>(grid_size);

    for (int j = 0; j < grid_size; j++) {
      board[i][j] = {' ', {i, j}};
    }
  }
}

int TicTacToe::get_grid_size() { return grid_size; }
const std::array<std::unique_ptr<Player>, 2> &TicTacToe::get_players() {
  return players;
}

int TicTacToe::get_board_center() {
  int square = std::pow(grid_size, 2);

  return square % 2 ? (square / 2) + 1 : (square / 2) - (grid_size / 2);
}

int TicTacToe::get_turn() { return turn; }
int TicTacToe::get_turn(const std::unique_ptr<Player> &player) {
  return &players[0] == &player ? 1 : 2;
}

void TicTacToe::update_turn() { turn = opposing_turn(turn); }

Board &TicTacToe::get_board() { return board; }
Cell &TicTacToe::get_cell(int pos) {
  return board[(pos - 1) / grid_size][(pos - 1) % grid_size];
}

std::vector<Cell> TicTacToe::get_empty_cells() {
  const int square = std::pow(grid_size, 2);

  int emp_c = 0;
  std::vector<Cell> empty_cells(square);

  for (int i = 0; i < square; i++) {
    int pos = i + 1;

    if (!has_mark(pos))
      empty_cells[emp_c++] = get_cell(pos);
  }

  empty_cells.resize(emp_c);

  return empty_cells;
}

void TicTacToe::map_board() {
  const std::string line = "|---------------|---------------|---------------|";

  std::cout << "\n" << line << "\n";

  for (int i = 0; i < grid_size; i++) {

    std::cout << "|\t";

    for (int j = 0; j < grid_size; j++) {
      std::cout << board[i][j].mark << "\t";

      if (j < grid_size - 1)
        std::cout << "|\t";
    }

    std::cout << "|\n" << line << "\n";
  }

  std::cout << "\n";
}

bool TicTacToe::has_mark(int pos) {
  int i = (pos - 1) / grid_size, j = (pos - 1) % grid_size;
  char cell_mark = board[i][j].mark;

  return cell_mark == players[0]->get_mark() ||
         cell_mark == players[1]->get_mark();
}

void TicTacToe::check(int turn) {
  std::unique_ptr<Player> &player = players[turn - 1];

  char mark = player->get_mark();

  std::vector<Orientation> horizontal = horizontal_orientations(turn),
                           vertical = vertical_orientations(turn),
                           diagonal = diagonal_orientations(turn);

  int h_size = horizontal.size(), v_size = vertical.size(),
      dg_size = diagonal.size();

  for (int i = 0; i < std::max(h_size, v_size); i++) {
    // Horizontal
    if (i < h_size) {
      bool valid = true;
      Orientation &orientation = horizontal[i];

      for (Cell &cell : orientation) {
        if (cell.mark == mark)
          continue;

        valid = false;

        break;
      }

      if (valid) {
        winner = std::move(player);

        break;
      }
    }

    // Vertical
    if (i < v_size) {
      bool valid = true;
      Orientation &orientation = vertical[i];

      for (Cell &cell : orientation) {
        if (cell.mark == mark)
          continue;

        valid = false;

        break;
      }

      if (valid) {
        winner = std::move(player);

        break;
      }
    }

    // Diagonal
    if (i < dg_size) {
      bool valid = true;
      Orientation &orientation = diagonal[i];

      for (Cell &cell : orientation) {
        if (cell.mark == mark)
          continue;

        valid = false;

        break;
      }

      if (valid) {
        winner = std::move(player);

        break;
      }
    }
  }
}

int TicTacToe::required_moves(const Orientation &orientation, int turn) {
  int moves = 0;

  std::unique_ptr<Player> &curr = players[turn - 1],
                          &opponent = players[opposing_turn(turn) - 1];

  if ((int)(orientation.size()) < grid_size)
    return grid_size;

  for (int i = 0; i < grid_size; i++) {
    Cell cell = orientation[i];

    // If there is a mark of the opponent, return 0
    // It is not a winning orientation any longer
    if (cell.mark == opponent->get_mark())
      return grid_size;

    // If the mark within the orientation is not the mark of the player of the
    // specified turn, it is an empty cell. Therefore, the amount of moves will
    // be further increased.
    if (cell.mark != curr->get_mark())
      moves++;
  }

  return moves;
}

Orientation TicTacToe::optimal_orientation(int turn) {
  Orientation orientation;
  int req_moves = INT_MAX;

  std::vector<Orientation> horizontal = horizontal_orientations(turn),
                           vertical = vertical_orientations(turn),
                           diagonal = diagonal_orientations(turn);

  int h_size = horizontal.size(), v_size = vertical.size(),
      dg_size = diagonal.size();

  std::function<void(Orientation &, int)> optimal =
      [&](Orientation &_orientation, int turn) -> void {
    std::function<void(Orientation &, int)> update =
        [&](Orientation &_orientation, int required) -> void {
      orientation = _orientation;
      req_moves = required;
    };

    int required = required_moves(_orientation, turn);
    if (required > req_moves)
      return;

    // Less than
    if (required < req_moves)
      update(_orientation, required);

    // Equal
    if (required == req_moves) {
      double rand = std::round(random() * 100);

      if (rand < 50)
        update(_orientation, required);
    }
  };

  for (int i = 0; i < std::max(h_size, v_size); i++) {
    // Horizontal
    if (i < h_size)
      optimal(horizontal[i], turn);

    // Vertical
    if (i < v_size) {
      optimal(vertical[i], turn);

      // Orientation &_orientation = vertical[i];
      // int required = required_moves(_orientation, turn);

      // if (required < req_moves) {
      //   orientation = _orientation;
      //   req_moves = required;
      // }
    }

    // Diagonal
    if (i < dg_size) {
      optimal(diagonal[i], turn);

      // Orientation &_orientation = diagonal[i];
      // int required = required_moves(_orientation, turn);

      // if (required < req_moves) {
      //   orientation = _orientation;
      //   req_moves = required;
      // }
    }
  }

  return orientation;
}

std::vector<Orientation> TicTacToe::horizontal_orientations(int turn) {
  std::unique_ptr<Player> &opponent = players[opposing_turn(turn) - 1];
  char opponent_mark = opponent->get_mark();

  std::vector<Orientation> orientations(grid_size);

  for (int i = 0; i < grid_size; i++) {
    bool valid = true;
    Orientation orientation(grid_size);

    for (int j = 0; j < grid_size; j++) {
      Cell cell = board[i][j];

      if (cell.mark != opponent_mark)
        orientation[j] = cell;
      else {
        valid = false;

        break;
      }
    }

    orientations[i] = valid ? std::move(orientation) : Orientation(grid_size);
  }

  return orientations;
}

std::vector<Orientation> TicTacToe::vertical_orientations(int turn) {
  std::unique_ptr<Player> &opponent = players[opposing_turn(turn) - 1];
  char opponent_mark = opponent->get_mark();

  std::vector<Orientation> orientations(grid_size);

  for (int i = 0; i < grid_size; i++) {
    bool valid = true;
    Orientation orientation(grid_size);

    for (int j = 0; j < grid_size; j++) {
      Cell cell = board[j][i];

      if (cell.mark != opponent_mark)
        orientation[j] = cell;
      else {
        valid = false;

        break;
      }
    }

    orientations[i] = valid ? std::move(orientation) : Orientation(grid_size);
  }

  return orientations;
}

std::vector<Orientation> TicTacToe::diagonal_orientations(int turn) {
  std::unique_ptr<Player> &opponent = players[opposing_turn(turn) - 1];

  const int do_n = 2;

  char opponent_mark = opponent->get_mark();
  std::vector<Orientation> orientations(do_n);

  bool valid[do_n] = {true, true};
  Orientation _orientations[do_n] = {Orientation(grid_size),
                                     Orientation(grid_size)};

  for (int i = 0; i < grid_size; i++) {

    // Diagonal
    // [i][i]
    {
      if (valid[0]) {
        Cell cell = board[i][i];

        if (cell.mark != opponent_mark)
          _orientations[0][i] = cell;
        else
          valid[0] = false;
      }
    }

    // Anti-Diagonal
    // [i][grid_size - (i + 1)]
    {
      if (valid[1]) {
        Cell cell = board[i][grid_size - (i + 1)];

        if (cell.mark != opponent_mark)
          _orientations[1][i] = cell;

        else
          valid[1] = false;
      }
    }
  }

  for (int i = 0; i < do_n; i++) {
    orientations[i] =
        valid[i] ? std::move(_orientations[i]) : Orientation(grid_size);
  }

  return orientations;
}

void TicTacToe::start() {
  // Map the board for an initial display
  map_board();

  // First turn
  players[turn - 1]->play(*this);
}

bool TicTacToe::process() {
  check(turn);

  if (winner != nullptr) {
    end();

    return true;
  } else if (!empty_slots) {
    end();

    return true;
  }

  update_turn();
  players[turn - 1]->play(*this);

  return false;
}

void TicTacToe::end() {
  if (winner == nullptr) {
    std::cout << "DRAW\n";
  } else
    std::cout << "WINNER: Player " << winner->get_mark() << "\n";
}

int TicTacToe::generate_random_pos() {
  return std::round(random() * std::pow((double)(grid_size), 2));
}