#pragma once

#include <array>
#include <cstdint>
#include <sys/types.h>

#include "tictactoe/constants.hpp"

struct PlayerConfiguration
{
    char mark;
    bool is_bot;

    struct BotConfiguration
    {
        uint32_t place_delay = 1'500;
        double accuracy = 50.0;
    } bot_config;
};

struct Configuration
{
    uint32_t grid_size = 3;
    ssize_t game_count = -1;
    bool auto_restart = false;
    std::array<PlayerConfiguration, TicTacToe::PLAYER_COUNT> players;
};

constexpr Configuration config{
    .grid_size = 3,
    .game_count = -1,
    .auto_restart = false,
    .players =
        {
            PlayerConfiguration{
                .mark = 'X',
                .is_bot = false,
            },
            PlayerConfiguration{
                .mark = 'O',
                .is_bot = true,
                .bot_config{.place_delay = 500, .accuracy = 100.0}},
        },
};

void start(const Configuration &config);
