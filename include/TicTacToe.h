#pragma once

#include <array>
#include <functional>
#include <memory>
#include <vector>

#include "Player.h"
#include "types.h"

class TicTacToe {
protected:
  int grid_size;
  std::array<std::unique_ptr<Player>, 2> &players;
  Board board;

  Player *winner;
  int turn;

  int empty_slots;

  void initialize_turn();
  void initialize_board();

  int generate_random_pos();

public:
  TicTacToe(int grid_size, std::array<std::unique_ptr<Player>, 2> &players);

  int get_grid_size();
  const std::array<std::unique_ptr<Player>, 2> &get_players();

  int get_board_center();

  int get_turn();
  int get_turn(const Player *player);

  void update_turn();

  Board &get_board();
  Cell &get_cell(int pos);

  std::vector<Cell> get_empty_cells();

  void map_board();
  bool has_mark(int pos);
  bool place_mark(int turn, int pos);

  void check(int turn);
  int required_moves(const Orientation &orientation, int turn);
  Orientation optimal_orientation(int turn);

  std::vector<Orientation> horizontal_orientations(int turn);
  std::vector<Orientation> vertical_orientations(int turn);
  std::vector<Orientation> diagonal_orientations(int turn);

  void start();
  void process();
  void end();
};