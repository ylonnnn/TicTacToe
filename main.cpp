#include "include/Bot.h"
#include "include/Player.h"
#include "include/TicTacToe.h"

#include <iostream>
#include <memory>

// If the game count is negative, the game will automatically restart
#define GAME_COUNT -1

// Grid Size
// 3 - 3x3
#define GRID_SIZE 3

// Modify
// 1 - Player VS Player
// 2 - Player VS Bot
#define GAME_MODE 2

// Modify player characters
#define PLAYER_1_CHAR 'X'
#define PLAYER_2_CHAR 'O'

// Modify bot settings
#define BOT_ACCURACY 25.0f

int main() {
  std::unique_ptr<Bot> bot =
      std::make_unique<Bot>(PLAYER_2_CHAR, 1'000, BOT_ACCURACY);

  // Create the opposing players (or bot)
  std::array<std::unique_ptr<Player>, 2> players = {
      std::make_unique<Player>(PLAYER_1_CHAR),
      GAME_MODE == 1 ? std::make_unique<Player>(PLAYER_2_CHAR)
                     : std::move(bot)};

  // Initialize the game
  TicTacToe game(GRID_SIZE, players);

  for (int i = 0; i != GAME_COUNT; i++) {
    std::cout << "\nGAME " << i + 1 << "\n";

    // Start the game
    game.start();
  }

  return 0;
}