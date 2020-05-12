//
// Created by petr on 9.5.17.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

//Board.h
class Board;

/**
    The base implementation of a player. It must be able to react to being on turn.
*/

class Player{
public:
    Player(bool w) : m_White (w){}

/**
    Executes the player's turn.

    @param board The chessboard being played on.
*/
    virtual void Play(Board & board)const = 0;
protected:
    bool m_White;
};

#endif //CHESS_PLAYER_H
