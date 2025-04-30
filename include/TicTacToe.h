#ifndef TICTACTOE_FILE_H
#define TICTACTOE_FILE_H

#include "Player.h"
#include <array>
#include <functional>
#include <memory>
#include <vector>

struct Cell {
  char mark;
  int position[2]; // [row][col]
};

using Board = std::vector<std::vector<Cell>>;
using Orientation = std::vector<Cell>;

class TicTacToe {
protected:
  int grid_size;
  std::array<std::unique_ptr<Player>, 2> &players;
  Board board;

  std::unique_ptr<Player> winner;
  int turn;

  void initialize_turn();
  void initialize_board();

  int generate_random_pos();

public:
  int empty_slots;

  TicTacToe(int grid_size, std::array<std::unique_ptr<Player>, 2> &players);

  int get_grid_size();
  const std::array<std::unique_ptr<Player>, 2> &get_players();

  int get_board_center();

  int get_turn();
  int get_turn(const std::unique_ptr<Player> &player);

  void update_turn();

  Board &get_board();
  Cell &get_cell(int pos);

  std::vector<Cell> get_empty_cells();

  void map_board();
  bool has_mark(int pos);

  void check(int turn);
  int required_moves(const Orientation &orientation, int turn);
  Orientation optimal_orientation(int turn);

  std::vector<Orientation> horizontal_orientations(int turn);
  std::vector<Orientation> vertical_orientations(int turn);
  std::vector<Orientation> diagonal_orientations(int turn);

  void start();
  bool process();
  void end();
};

#endif