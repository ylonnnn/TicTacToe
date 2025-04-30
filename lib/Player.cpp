#include "../include/TicTacToe.h"
#include "../include/utils.h"

#include <cmath>
#include <iostream>
#include <memory>

Player::Player(char mark) : mark(mark){};

char Player::get_mark() const { return mark; }

int Player::get_turn(TicTacToe &game) const {
  return game.get_turn(std::make_unique<Player>(*this));
}

void Player::play(TicTacToe &game) {
  Board &board = game.get_board();
  int pos, turn = game.get_turn(std::make_unique<Player>(*this));

  std::cout << "[" << turn << "] Enter the Mark Position [" << mark << "]: ";
  std::cin >> pos;

  int grid_size = game.get_grid_size(), max_pos = std::pow(grid_size, 2);

  if (pos < 1 || pos > max_pos || std::cin.fail()) {
    std::cout << "Invalid position! Valid positions range from 1 to " << max_pos
              << "\n";

    return play(game);
  }

  // If one of the players' marks are in that cell, it has already been marked
  if (game.has_mark(pos)) {
    std::cout << "This position is already marked!\n";

    return play(game);
  }

  board[(pos - 1) / grid_size][(pos - 1) % grid_size].mark = mark;
  game.empty_slots--;

  // Map the board and process the played turn
  game.map_board();
  game.process();
}