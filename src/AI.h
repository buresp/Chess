//
// Created by petr on 9.5.17.
//

#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <utility>
#include "Player.h"

/**
    The implementation of an AI. It uses Minimax algorithm to choose a move.
*/

class AI : public Player{
public:
    AI(bool w) : Player(w){}

/**
    Executes the AI's turn.

    @param board The chessboard being played on.
*/
    virtual void Play(Board & board)const;
};

#endif //CHESS_AI_H
