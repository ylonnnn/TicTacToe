#pragma once

#include "Player.h"

class Bot : public Player {
protected:
  int place_delay;
  float accuracy;

public:
  Bot(char mark);
  Bot(char mark, int place_delay);
  Bot(char mark, int place_delay, float accuracy);

  int get_place_delay() const;
  float get_accuracy() const;

  int decide_position(TicTacToe &game);

  void play(TicTacToe &game) override;
};