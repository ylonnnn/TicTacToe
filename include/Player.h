#pragma once

class TicTacToe;

class Player {
protected:
  char mark;

public:
  Player(char mark);

  char get_mark() const;
  int get_turn(TicTacToe &game) const;

  virtual void play(TicTacToe &game);
};
