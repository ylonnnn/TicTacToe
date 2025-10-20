#include <array>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "player/Player.hpp"
#include "tictactoe/Cell.hpp"
#include "tictactoe/TicTacToe.hpp"
#include "tictactoe/constants.hpp"
#include "utils/random.hpp"

namespace TicTacToe
{
    TicTacToe::TicTacToe(uint32_t grid_size,
                         std::array<std::unique_ptr<Player>, 2> &&players)
        : grid_size_(grid_size)
    {
        for (size_t i = 0; i < players.size(); ++i)
            turns_[i] = std::make_unique<Turn>(i + 1, std::move(players[i]));
    }

    void TicTacToe::initialize_turn()
    {
        current_turn_ = std::round(utils::random::generate());
    }

    void TicTacToe::initialize_board()
    {
        auto area = std::pow(grid_size_, 2);

        board_.clear();
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

    Turn *TicTacToe::turn(size_t no) { return turns_[no].get(); }

    const Turn *TicTacToe::turn(size_t no) const { return turns_[no].get(); }

    Turn *TicTacToe::turn(const Player &player)
    {
        for (auto &turn : turns_)
            if (&turn->player() == &player)
                return turn.get();

        return nullptr;
    }

    const Turn *TicTacToe::turn(const Player &player) const
    {
        for (auto &turn : turns_)
            if (&turn->player() == &player)
                return turn.get();

        return nullptr;
    }

    size_t TicTacToe::current_turn() const { return current_turn_; }

    size_t TicTacToe::opposing_turn() const
    {
        return opposing_turn(current_turn_);
    }

    size_t TicTacToe::opposing_turn(size_t turn_no) const
    {
        return (turn_no + 1) % PLAYER_COUNT;
    }

    Cell &TicTacToe::cell_at(uint32_t pos) { return board_[pos]; }

    std::vector<Cell *> TicTacToe::empty_cells() const
    {
        std::vector<Cell *> empty;
        empty.reserve(std::pow(grid_size_, 2));

        for (auto &cell : board_)
            if (!cell.marked())
                empty.push_back(const_cast<Cell *>(&cell));

        return empty;
    }

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

    void TicTacToe::check(Turn &turn)
    {
        Orientation optimal = optimal_orientation(turn);
        if (optimal.cells.empty())
            return;

        uint32_t required = optimal.required_moves();
        if (required == 0)
            winner_ = &turn;
    }

    Orientation TicTacToe::optimal_orientation(Turn &turn)
    {
        Orientation orientation{*this, turn};
        uint32_t req_moves = UINT32_MAX;

        std::vector<Orientation> horizontal = horizontal_orientations(turn),
                                 vertical = vertical_orientations(turn),
                                 diagonal = diagonal_orientations(turn);

        int h_size = horizontal.size(), v_size = vertical.size(),
            dg_size = diagonal.size();

        auto optimal = [&](Orientation &_orientation, Turn &turn) -> void
        {
            if (_orientation.cells.size() == 0)
                return;

            auto update = [&](Orientation &_orientation,
                              uint32_t required) -> void
            {
                orientation.cells = std::move(_orientation.cells);
                req_moves = required;
            };

            uint32_t required = _orientation.required_moves();
            if (required > req_moves)
                return;

            // Less than
            if (required < req_moves)
                update(_orientation, required);

            // Equal
            else if ((required == req_moves) && random() * 100 < 50)
                update(_orientation, required);
        };

        for (int i = 0; i < std::max({h_size, v_size, dg_size}); i++)
        {
            // Horizontal
            if (i < h_size)
                optimal(horizontal[i], turn);

            // Vertical
            if (i < v_size)
            {
                optimal(vertical[i], turn);
            }

            // Diagonal
            if (i < dg_size)
            {
                optimal(diagonal[i], turn);
            }
        }

        return orientation;
    }

    std::vector<Orientation> TicTacToe::horizontal_orientations(Turn &turn)
    {
        std::vector<Orientation> orientations;
        orientations.reserve(grid_size_);

        for (int i = 0; i < grid_size_; ++i)
        {
            Orientation orientation{*this, turn};
            orientation.cells.reserve(grid_size_);

            for (int j = 0; j < grid_size_; ++j)
            {
                Cell &cell = board_[i * grid_size_ + j];
                char mark = cell.mark();

                if (mark != EMPTY_CHAR && mark != turn.player().mark())
                    break;

                orientation.cells.push_back(&cell);
            }

            if (orientation.cells.size() < static_cast<size_t>(grid_size_))
                continue;

            orientations.push_back(std::move(orientation));
        }

        return orientations;
    }

    std::vector<Orientation> TicTacToe::vertical_orientations(Turn &turn)
    {
        std::vector<Orientation> orientations;
        orientations.reserve(grid_size_);

        for (int i = 0; i < grid_size_; ++i)
        {
            Orientation orientation{*this, turn};
            orientation.cells.reserve(grid_size_);

            for (int j = 0; j < grid_size_; ++j)
            {
                Cell &cell = board_[j * grid_size_ + i];
                char mark = cell.mark();

                if (mark != EMPTY_CHAR && mark != turn.player().mark())
                    break;

                orientation.cells.push_back(&cell);
            }

            if (orientation.cells.size() < static_cast<size_t>(grid_size_))
                continue;

            orientations.push_back(std::move(orientation));
        }

        return orientations;
    }

    std::vector<Orientation> TicTacToe::diagonal_orientations(Turn &turn)
    {
        constexpr uint32_t do_n = 2;

        std::vector<Orientation> orientations;
        orientations.reserve(do_n);

        bool valid[do_n] = {true, true};
        std::array<Orientation, do_n> _orientations{Orientation{*this, turn},
                                                    {*this, turn}};

        _orientations[0].cells.reserve(grid_size_);
        _orientations[1].cells.reserve(grid_size_);

        for (int i = 0; i < grid_size_; ++i)
        {
            // Diagonal
            // [i][i]
            {
                if (valid[0])
                {
                    Cell &cell = board_[i * grid_size_ + i];
                    char mark = cell.mark();

                    if (mark != EMPTY_CHAR && mark != turn.player().mark())
                        valid[0] = false;

                    _orientations[0].cells.push_back(&cell);
                }
            }

            // Anti-Diagonal
            // [i][grid_size - (i + 1)]
            {
                if (valid[1])
                {
                    Cell &cell =
                        board_[(i * grid_size_) + grid_size_ - (i + 1)];
                    char mark = cell.mark();

                    if (mark != EMPTY_CHAR && mark != turn.player().mark())
                        valid[1] = false;

                    _orientations[1].cells.push_back(&cell);
                }
            }
        }

        for (int i = 0; i < do_n; i++)
        {
            if (valid[i])
                orientations.push_back(std::move(_orientations[i]));
        }

        return orientations;
    }

    void TicTacToe::start()
    {
        // Initialize the turn and board
        initialize_turn();
        initialize_board();

        // Map the board for an initial display
        map_board();

        // First turn
        turns_[current_turn_]->player().play(*this);
    }

    void TicTacToe::process()
    {
        ++placement;

        check(*turns_[current_turn_]);

        if (winner_ != nullptr || placement == board_.size())
        {
            end();
            return;
        }

        current_turn_ = (current_turn_ + 1) % PLAYER_COUNT;
        turns_[current_turn_]->player().play(*this);
    }

    void TicTacToe::end()
    {
        // TODO: Game End
        if (winner_ == nullptr)
        {
            std::cout << "DRAW\n";
        }

        else
            std::cout << "WINNER: Player " << winner_->player().mark() << "\n";

        winner_ = nullptr;
    }

} // namespace TicTacToe
