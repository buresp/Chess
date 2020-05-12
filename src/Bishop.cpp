//
// Created by petr on 8.5.17.
//

#include "Bishop.h"
#include "Board.h"
#include "Queen.h"

Bishop::Bishop(bool w){
    m_White = w;
}
char Bishop::Type()const{
    return 'B';
}

bool Bishop::IsWhite()const {
    return m_White;
}

Piece * Bishop::Clone() const {
    return new Bishop(m_White);
}

/**
    Creates a collection of possible moves.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return A collection of the possible moves.
*/

Moveset Bishop::GetMoves(const Board & board, const int &x, const int &y) const{
    Moveset moves;
    Queen::TryDirection(moves, board, x, y, 1, 1);
    Queen::TryDirection(moves, board, x, y, 1, -1);
    Queen::TryDirection(moves, board, x, y, -1, -1);
    Queen::TryDirection(moves, board, x, y, -1, 1);
    return moves;
}