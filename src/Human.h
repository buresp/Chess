//
// Created by petr on 9.5.17.
//

#ifndef CHESS_HUMAN_H
#define CHESS_HUMAN_H

#include "Player.h"

/**
    The implementation of Human. When on turn, it asks the player
    to move a chess piece or save the game until it successfully makes a move.
*/

class Human : public Player{
public:
    Human(bool w) : Player(w){}

/**
    Executes the player's turn. Asks for input.

    @param board The chessboard being played on.
*/
    virtual void Play(Board & board)const;

/**
    Asks what should a pawn be promoted to.

    @param board The chessboard being played on.
    @param x The row index of the pawn.
    @param y The column index of the pawn.
*/
    void Promotion(Board & board, const int &x, const int &y)const;
};

#endif //CHESS_HUMAN_H
