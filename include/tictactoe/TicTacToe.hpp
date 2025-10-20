#pragma once

#include <array>
#include <cstdint>
#include <memory>

#include "tictactoe/Cell.hpp"
#include "tictactoe/Turn.hpp"
#include "tictactoe/constants.hpp"

namespace TicTacToe
{
    class TicTacToe
    {
      public:
        TicTacToe(uint32_t grid_size,
                  std::array<std::unique_ptr<Player>, PLAYER_COUNT> &&players);

        uint32_t grid_size() const;
        uint32_t board_center() const;

        Turn &turn();
        const Turn &turn() const;

        Turn *turn(size_t no);
        const Turn *turn(size_t no) const;

        Turn *turn(const Player &player);
        const Turn *turn(const Player &player) const;

        size_t current_turn() const;

        size_t opposing_turn() const;
        size_t opposing_turn(size_t turn_no) const;

        Cell &cell_at(uint32_t pos);

        std::vector<Cell *> empty_cells() const;

        void map_board() const;

        void check(Turn &turn);

        Orientation optimal_orientation(Turn &turn);

        std::vector<Orientation> horizontal_orientations(Turn &turn);
        std::vector<Orientation> vertical_orientations(Turn &turn);
        std::vector<Orientation> diagonal_orientations(Turn &turn);

        void start();
        void process();
        void end();

      private:
        void initialize_turn();
        void initialize_board();

        size_t generate_random_pos();

      private:
        uint32_t grid_size_;
        std::vector<Cell> board_;

        uint32_t current_turn_ = 0;
        uint32_t placement = 0;

        std::array<std::unique_ptr<Turn>, PLAYER_COUNT> turns_;

        Turn *winner_ = nullptr;
    };

} // namespace TicTacToe
