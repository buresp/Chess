//
// Created by petr on 8.5.17.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "Moveset.h"
//Board.h
class Board;

/**
    The implementation of the base chess Piece. Each chess piece has to have a
    type, color and needs to be able to determine its possible moves and make a deep copy.
*/

class Piece{
public:
    Piece() {}
    virtual ~Piece(){}

/**
    Returns the type of the chess piece represented as a character.

    @return The character representing the type.
*/
    virtual char Type() const = 0;

/**
    Indicates if the chess piece is white.

    @return The value indicating the chess piece's color.
*/
    virtual bool IsWhite() const = 0;

/**
    Indicates if a chess piece has been moved this game.

    @return The value indicating if the chess piece has been moved.
*/
    inline virtual bool GetMoved()const {return false;}

/**
    Sets the moved value to true if the object keeps that value.
*/
    inline virtual void Moved() {}

/**
    Calculates all possible moves of a chess piece.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return The pointer to the copy.
*/
    virtual Moveset GetMoves(const Board & board, const int &x, const int &y) const = 0;

/**
    Returns a pointer to a deep copy of this chess piece.

    @return The pointer to the copy.
*/
    virtual Piece * Clone() const = 0;
};

#endif //CHESS_PIECE_H
