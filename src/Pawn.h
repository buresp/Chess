//
// Created by petr on 8.5.17.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

/**
    The implementation of the Pawn chess piece.
*/

class Pawn : public Piece{
public:
    Pawn(bool w);
    virtual ~Pawn(){}

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
    Indicates if a chess piece has been moved this game.

    @return The value indicating if the chess piece has been moved.
*/
    inline virtual bool GetMoved()const {return m_Moved;}

/**
    Sets the moved value to true;
*/
    inline virtual void Moved() {m_Moved = true;}

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
private:
    bool m_White;
    bool m_Moved;
};

#endif //CHESS_PAWN_H
