#include <iostream>
#include <memory>
#include <string>

#include "include/Bot.h"
#include "include/Player.h"
#include "include/TicTacToe.h"

// If the game count is negative, the game will automatically restart
#define GAME_COUNT -1

// Whether the game will automatically restart or press [Enter] before
// proceeding
#define AUTO_GAME_RESTART false

// Grid Size
// 3 - 3x3
#define GRID_SIZE 3

// Modify
// 1 - Player VS Player
// 2 - Player VS Bot
// 3 - Bot VS Bot
#define GAME_MODE 3

#define PLAYER_1_CHAR 'X'

// Bot 1 Settings
#define BOT_1_PLACE_DELAY 1'000
#define BOT_1_ACCURACY 100.0f

#define PLAYER_2_CHAR 'O'

// Bot 1 Settings
#define BOT_2_PLACE_DELAY 1'000
#define BOT_2_ACCURACY 100.0f

int main() {
  // Create the players
  std::array<std::unique_ptr<Player>, 2> players = {
      GAME_MODE == 3 ? std::make_unique<Bot>(PLAYER_1_CHAR, BOT_1_PLACE_DELAY,
                                             BOT_1_ACCURACY)
                     : std::make_unique<Player>(PLAYER_1_CHAR),
      GAME_MODE == 1 ? std::make_unique<Player>(PLAYER_2_CHAR)
                     : std::make_unique<Bot>(PLAYER_2_CHAR, BOT_2_PLACE_DELAY,
                                             BOT_2_ACCURACY)};

  // Initialize the game
  TicTacToe game(GRID_SIZE, players);

  for (int i = 0; i != GAME_COUNT; i++) {
    std::cout << "\nGAME " << i + 1 << "\n";

    // Start the game
    game.start();

    if (AUTO_GAME_RESTART)
      continue;
    else {
      std::string input;

      std::cout << "Please press [Enter] to continue\n";
      std::getline(std::cin, input);
    }
  }

  return 0;
}