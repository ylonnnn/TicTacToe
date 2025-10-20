#pragma once

namespace TicTacToe
{
    class TicTacToe;

    class Player
    {
      protected:
        char mark_;

      public:
        Player(char mark);

        char mark() const;

        virtual void play(TicTacToe &game);
    };

} // namespace TicTacToe
