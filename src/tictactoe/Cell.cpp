#include "tictactoe/Cell.hpp"
#include <cassert>

namespace TicTacToe
{
    Cell::Cell(uint32_t absolute_pos, std::array<uint32_t, 2> &&pos)
        : absolute_pos_(absolute_pos), pos_(std::move(pos))
    {
    }

    const std::array<uint32_t, 2> Cell::position() const { return pos_; }

    char Cell::mark() const
    {
        return turn_ == nullptr ? '\0' : turn_->player().mark();
    }

    bool Cell::marked() const { return mark() != '\0'; }

    bool Cell::place(Turn *turn)
    {
        assert(turn != nullptr);

        if (marked())
            return false;

        turn_ = turn;

        return true;
    }

} // namespace TicTacToe
