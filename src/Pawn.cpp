//
// Created by petr on 8.5.17.
//

#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(bool w){
    m_White = w;
    m_Moved = false;
}
char Pawn::Type()const{
    return 'P';
}

bool Pawn::IsWhite()const{
    return m_White;
}

Piece * Pawn::Clone() const {
    Pawn * clone = new Pawn(m_White);
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

Moveset Pawn::GetMoves(const Board & board, const int &x, const int &y) const{
    Moveset moves;
    if(!m_Moved) {
        if (x < 6 && !m_White && board[x + 2][y]->Type() == 'E'&& board[x + 1][y]->Type() == 'E'){
            moves.AddMove(x+2, y);
        }
        if (x > 1 && m_White && board[x - 2][y]->Type() == 'E' && board[x - 1][y]->Type() == 'E'){
            moves.AddMove(x-2, y);
        }
    }
    if (x < 7 && !m_White && board[x + 1][y]->Type() == 'E'){
        moves.AddMove(x+1, y);
    }
    if (x > 0 && m_White && board[x - 1][y]->Type() == 'E'){
        moves.AddMove(x-1, y);
    }
    if(!m_White) {
        if (x < 7 && y < 7 && board[x + 1][y + 1]->Type() != 'E' && board[x + 1][y + 1]->IsWhite())
            moves.AddMove(x+1, y+1);
        if (x < 7 && y > 0 && board[x + 1][y - 1]->Type() != 'E' && board[x + 1][y - 1]->IsWhite())
            moves.AddMove(x+1, y-1);
    }
    if(m_White) {
        if (x > 0 && y < 7 && board[x - 1][y + 1]->Type() != 'E' && !board[x - 1][y + 1]->IsWhite())
            moves.AddMove(x-1, y+1);
        if (x > 0 && y > 0 && board[x - 1][y - 1]->Type() != 'E' && !board[x - 1][y - 1]->IsWhite())
            moves.AddMove(x-1, y-1);
    }
    return moves;
}