#include "tictactoe/Cell.hpp"
#include "tictactoe/TicTacToe.hpp"
#include "tictactoe/constants.hpp"

namespace TicTacToe
{
    Cell::Cell(uint32_t absolute_pos, std::array<uint32_t, 2> &&pos)
        : absolute_pos_(absolute_pos), pos_(std::move(pos))
    {
    }

    uint32_t Cell::absolute_pos() const { return absolute_pos_; }

    const std::array<uint32_t, 2> Cell::position() const { return pos_; }

    char Cell::mark() const
    {
        return turn_ == nullptr ? EMPTY_CHAR : turn_->player().mark();
    }

    bool Cell::marked() const { return mark() != EMPTY_CHAR; }

    bool Cell::place(Turn &turn)
    {
        if (marked())
            return false;

        turn_ = &turn;

        return true;
    }

    Orientation::Orientation(TicTacToe &game, Turn &turn)
        : game(game), turn(turn)
    {
    }

    uint32_t Orientation::required_moves() const
    {
        if (cells.size() < game.grid_size())
            return UINT32_MAX;

        uint32_t required = 0;

        for (const auto &cell : cells)
            if (!cell->marked())
                ++required;

        return required;
    }

} // namespace TicTacToe
