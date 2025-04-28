#include "Player.h"
#include <array>
#include <memory>

class TicTacToe {
protected:
  int grid_size;
  std::array<Player, 2> players;
  char **board;

  std::unique_ptr<Player> winner;
  int turn;

  void initialize_turn();
  void initialize_board();

public:
  TicTacToe(const int &grid_size, std::array<Player, 2> players);

  int get_turn();

  void map_board();
  void pos_prompt();

  void check(int turn);

  char **horizontal_orientations(int turn);
  char **vertical_orientations(int turn);
  char **diagonal_orientations(int turn);

  void start();

  void end();
};