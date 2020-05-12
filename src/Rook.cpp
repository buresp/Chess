//
// Created by petr on 8.5.17.
//

#include "Rook.h"
#include "Board.h"
#include "Queen.h"

Rook::Rook(bool w){
    m_White = w;
    m_Moved = false;
}
char Rook::Type()const{
    return 'R';
}

bool Rook::IsWhite()const {
    return m_White;
}

Piece * Rook::Clone() const {
    Rook * clone = new Rook(m_White);
    clone->m_Moved = m_Moved;
    return clone;
}

/**
    Creates a collection of possible moves.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return A collection of the possible moves.
*/

Moveset Rook::GetMoves(const Board & board, const int &x, const int &y) const{
    Moveset moves;
    Queen::TryDirection(moves, board, x, y, 0, 1);
    Queen::TryDirection(moves, board, x, y, 0, -1);
    Queen::TryDirection(moves, board, x, y, 1, 0);
    Queen::TryDirection(moves, board, x, y, -1, 0);
    return moves;
}