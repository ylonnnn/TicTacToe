#include "include/TicTacToe.h"
#include <iostream>

int main() {
  //

  std::array<Player, 2> players = {Player('X'), Player('O')};

  TicTacToe tictactoe(3, players);

  tictactoe.map_board();

  std::cout << tictactoe.get_turn() << "\n";

  tictactoe.start();

  return 0;
}