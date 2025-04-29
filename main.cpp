#include "include/Bot.h"
#include "include/Player.h"
#include "include/TicTacToe.h"
#include <memory>

int main() {
  std::unique_ptr<Bot> bot = std::make_unique<Bot>('O', 1'000, 100);

  // Create two players
  std::array<std::unique_ptr<Player>, 2> players = {
      std::make_unique<Player>('X'), std::move(bot)};

  // Initialize the game
  TicTacToe game(3, players);

  // Start the game
  game.start();

  return 0;
}