//
// Created by petr on 8.5.17.
//

#ifndef CHESS_EMPTY_H
#define CHESS_EMPTY_H

#include "Piece.h"

/**
    The implementation of an empty position on the chessboard.
*/

class Empty : public Piece{
public:
    Empty();
    virtual ~Empty(){}

/**
    Returns the type of the chess piece represented as a character.

    @return The character representing the type.
*/
    virtual char Type()const;

/**
    Indicates if the chess piece is white.

    @return The value indicating the chess piece's color.
*/
    virtual bool IsWhite()const;

/**
    Calculates all possible moves of a chess piece.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return The pointer to the copy.
*/
    virtual Moveset GetMoves(const Board & board, const int &x, const int &y) const;

/**
    Returns a pointer to a deep copy of this chess piece.

    @return The pointer to the copy.
*/
    virtual Piece * Clone() const;
};

#endif //CHESS_EMPTY_H
