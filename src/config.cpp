#include <iostream>

#include "config.hpp"
#include "player/Bot.hpp"
#include "player/Player.hpp"
#include "tictactoe/TicTacToe.hpp"
#include "tictactoe/constants.hpp"

void start(const Configuration &config)
{
    std::array<std::unique_ptr<TicTacToe::Player>, TicTacToe::PLAYER_COUNT>
        players;

    for (size_t i = 0; i < config.players.size(); ++i)
    {
        const auto &[mark, is_bot, bot_config] = config.players[i];

        players[i] =
            is_bot ? std::make_unique<TicTacToe::Bot>(
                         mark, bot_config.place_delay, bot_config.accuracy)
                   : std::make_unique<TicTacToe::Player>(mark);
    }

    TicTacToe::TicTacToe game(config.grid_size, std::move(players));

    for (size_t i = 0; i != config.game_count; ++i)
    {
        std::cout << "\nGAME " << (i + 1) << "\n";

        // Start the game
        game.start();

        if (config.auto_restart)
            continue;
        else
        {
            std::cout << "Please press [Enter] to continue\n";

            std::string input;
            std::getline(std::cin, input);
        }
    }
}
