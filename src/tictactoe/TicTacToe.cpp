#include <array>
#include <climits>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "player/Player.hpp"
#include "tictactoe/Cell.hpp"
#include "tictactoe/TicTacToe.hpp"
#include "utils/random.hpp"

namespace TicTacToe
{
    TicTacToe::TicTacToe(uint32_t grid_size,
                         std::array<std::unique_ptr<Player>, 2> &&players)
        : grid_size_(grid_size)
    {
        for (size_t i = 0; i < players.size(); ++i)
            turns_[i] = std::make_unique<Turn>(i + 1, std::move(players[i]));

        initialize_turn();
        initialize_board();
    }

    void TicTacToe::initialize_turn()
    {
        current_turn_ = std::round(utils::random::generate());
    }

    void TicTacToe::initialize_board()
    {
        auto area = std::pow(grid_size_, 2);
        board_.reserve(area);

        for (uint32_t i = 0; i < area; ++i)
            board_.emplace_back(i, std::array<uint32_t, 2>{i / 3, i % 3});
    }

    size_t TicTacToe::generate_random_pos()
    {
        return static_cast<size_t>(
            std::round(utils::random::generate() *
                       static_cast<double>(std::pow(grid_size_, 2))));
    }

    uint32_t TicTacToe::grid_size() const { return grid_size_; }

    uint32_t TicTacToe::board_center() const
    {
        uint32_t square = std::pow(grid_size_, 2);

        return square % 2 ? (square / 2) + 1 : (square / 2) - (grid_size_ / 2);
    }

    Turn &TicTacToe::turn() { return *turns_[current_turn_]; }
    const Turn &TicTacToe::turn() const { return *turns_[current_turn_]; }

    Cell &TicTacToe::cell_at(uint32_t pos) { return board_[pos]; }

    void TicTacToe::map_board() const
    {
        const std::string line = "|---------------";
        const auto print_line = [&]() -> void
        {
            for (size_t i = 0; i < grid_size_; ++i)
                std::cout << line;
            std::cout << "|\n";
        };

        std::cout << "\n";
        print_line();

        for (int i = 0; i < grid_size_; ++i)
        {
            std::cout << "|\t";

            for (int j = 0; j < grid_size_; ++j)
            {
                std::cout << board_[i * grid_size_ + j].mark() << "\t";

                if (j < grid_size_ - 1)
                    std::cout << "|\t";
            }

            std::cout << "|\n";
            print_line();
        }

        std::cout << "\n";
    }

    // bool TicTacToe::has_mark(int pos)
    // {
    //     int i = (pos - 1) / grid_size, j = (pos - 1) % grid_size;
    //     char cell_mark = board[i][j].mark;

    //     return cell_mark == players[0]->get_mark() ||
    //            cell_mark == players[1]->get_mark();
    // }

    // bool TicTacToe::place_mark(int turn, int pos)
    // {
    //     int square = std::pow(grid_size, 2);

    //     if ((pos < 1) || (pos > square) || has_mark(pos))
    //         return false;

    //     empty_slots--;
    //     board[(pos - 1) / grid_size][(pos - 1) % grid_size].mark =
    //         players[turn - 1]->get_mark();

    //     check(turn);

    //     return true;
    // }

    // void TicTacToe::check(int turn)
    // {
    //     Orientation optimal = optimal_orientation(turn);
    //     int required = required_moves(optimal, turn);

    //     if (required == 0)
    //     {
    //         winner = players[turn - 1].get();
    //     }
    // }

    // int TicTacToe::required_moves(const Orientation &orientation, int turn)
    // {
    //     int moves = 0;

    //     std::unique_ptr<Player> &curr = players[turn - 1],
    //                             &opponent = players[opposing_turn(turn) - 1];

    //     if ((int)(orientation.size()) < grid_size)
    //         return grid_size;

    //     for (int i = 0; i < grid_size; i++)
    //     {
    //         Cell cell = orientation[i];

    //         // If there is a mark of the opponent, return 0
    //         // It is not a winning orientation any longer
    //         if (cell.mark == opponent->get_mark())
    //             return grid_size;

    //         // If the mark within the orientation is not the mark of the
    //         player
    //         // of the specified turn, it is an empty cell. Therefore, the
    //         amount
    //         // of moves will be further increased.
    //         if (cell.mark != curr->get_mark())
    //             moves++;
    //     }

    //     return moves;
    // }

    // Orientation TicTacToe::optimal_orientation(int turn)
    // {
    //     Orientation orientation;
    //     int req_moves = INT_MAX;

    //     std::vector<Orientation> horizontal = horizontal_orientations(turn),
    //                              vertical = vertical_orientations(turn),
    //                              diagonal = diagonal_orientations(turn);

    //     int h_size = horizontal.size(), v_size = vertical.size(),
    //         dg_size = diagonal.size();

    //     std::function<void(Orientation &, int)> optimal =
    //         [&](Orientation &_orientation, int turn) -> void
    //     {
    //         if (_orientation.size() == 0)
    //             return;

    //         std::function<void(Orientation &, int)> update =
    //             [&](Orientation &_orientation, int required) -> void
    //         {
    //             orientation = _orientation;
    //             req_moves = required;
    //         };

    //         int required = required_moves(_orientation, turn);
    //         if (required > req_moves)
    //             return;

    //         // Less than
    //         if (required < req_moves)
    //             update(_orientation, required);

    //         // Equal
    //         else if ((required == req_moves) && random() * 100 < 50)
    //             update(_orientation, required);
    //     };

    //     for (int i = 0; i < std::max({h_size, v_size, dg_size}); i++)
    //     {
    //         // Horizontal
    //         if (i < h_size)
    //             optimal(horizontal[i], turn);

    //         // Vertical
    //         if (i < v_size)
    //         {
    //             optimal(vertical[i], turn);
    //         }

    //         // Diagonal
    //         if (i < dg_size)
    //         {
    //             optimal(diagonal[i], turn);
    //         }
    //     }

    //     return orientation;
    // }

    // std::vector<Orientation> TicTacToe::horizontal_orientations(int turn)
    // {
    //     char opponent_mark = players[opposing_turn(turn) - 1]->get_mark();

    //     std::vector<Orientation> orientations;
    //     orientations.reserve(grid_size);

    //     for (int i = 0; i < grid_size; i++)
    //     {
    //         Orientation orientation;
    //         orientation.reserve(grid_size);

    //         for (int j = 0; j < grid_size; j++)
    //         {
    //             Cell cell = board[i][j];

    //             if (cell.mark == opponent_mark)
    //                 break;

    //             orientation.push_back(cell);
    //         }

    //         if ((int)(orientation.size()) < grid_size)
    //             continue;

    //         orientations.push_back(std::move(orientation));
    //     }

    //     return orientations;
    // }

    // std::vector<Orientation> TicTacToe::vertical_orientations(int turn)
    // {
    //     char opponent_mark = players[opposing_turn(turn) - 1]->get_mark();

    //     std::vector<Orientation> orientations;
    //     orientations.reserve(grid_size);

    //     for (int i = 0; i < grid_size; i++)
    //     {
    //         Orientation orientation;
    //         orientation.reserve(grid_size);

    //         for (int j = 0; j < grid_size; j++)
    //         {
    //             Cell cell = board[j][i];

    //             if (cell.mark == opponent_mark)
    //                 break;

    //             orientation.push_back(cell);
    //         }

    //         if ((int)(orientation.size()) < grid_size)
    //             continue;

    //         orientations.push_back(std::move(orientation));
    //     }

    //     return orientations;
    // }

    // std::vector<Orientation> TicTacToe::diagonal_orientations(int turn)
    // {
    //     const int do_n = 2;

    //     char opponent_mark = players[opposing_turn(turn) - 1]->get_mark();
    //     std::vector<Orientation> orientations(do_n);

    //     bool valid[do_n] = {true, true};
    //     Orientation _orientations[do_n];

    //     _orientations[0].reserve(grid_size);
    //     _orientations[1].reserve(grid_size);

    //     for (int i = 0; i < grid_size; i++)
    //     {
    //         // Diagonal
    //         // [i][i]
    //         {
    //             if (valid[0])
    //             {
    //                 Cell cell = board[i][i];

    //                 if (cell.mark == opponent_mark)
    //                     valid[0] = false;

    //                 _orientations[0].push_back(cell);
    //             }
    //         }

    //         // Anti-Diagonal
    //         // [i][grid_size - (i + 1)]
    //         {
    //             if (valid[1])
    //             {
    //                 Cell cell = board[i][grid_size - (i + 1)];

    //                 if (cell.mark == opponent_mark)
    //                     valid[1] = false;

    //                 _orientations[1].push_back(cell);
    //             }
    //         }
    //     }

    //     for (int i = 0; i < do_n; i++)
    //     {
    //         if (valid[i])
    //             orientations.push_back(std::move(_orientations[i]));
    //     }

    //     return orientations;
    // }

    void TicTacToe::start()
    {
        // Map the board for an initial display
        map_board();

        // First turn
        turns_[current_turn_]->player().play(*this);
    }

    void TicTacToe::process()
    {
        // check(turn);

        // if (winner != nullptr)
        // {
        //     end();

        //     return;
        // }
        // else if (!empty_slots)
        // {
        //     end();

        //     return;
        // }

        current_turn_ = (current_turn_ + 1) % 2;
        turns_[current_turn_]->player().play(*this);
    }

    void TicTacToe::end()
    {
        // TODO: Game End
        // if (winner == nullptr)
        // {
        //     std::cout << "DRAW\n";
        // }
        // else
        //     std::cout << "WINNER: Player " << winner->get_mark() << "\n";

        // winner = nullptr;
    }

} // namespace TicTacToe
