//
// Created by petr on 8.5.17.
//

#include "King.h"
#include "Board.h"

King::King(bool w){
    m_White = w;
    m_Moved = false;
}
char King::Type()const{
    return 'K';
}

bool King::IsWhite()const {
    return m_White;
}

Piece * King::Clone() const {
    King * clone = new King(m_White);
    clone->m_Moved = m_Moved;
    return clone;
}

/**
    Checks if the positions between the king and the rook are empty.

    @param board The chessboard the chess piece is on.
    @param x The row index of the king.
    @param from The lesser column index of the king or the rook.
    @param to The higher column index of the king or the rook.
    @return Indicates if the positions are empty.
*/

bool ClearPassage(const Board & board, const int & x, int from, int to){
    while (from + 1 < to)
        if(board[x][++from]->Type() != 'E')
            return false;
    while (from - 1 > to)
        if(board[x][--from]->Type() != 'E')
            return false;
    return true;
}

/**
    Adds castling moves to the possible moves of a rook.

    @param moves The possible moves of a chess piece.
    @param board The chessboard the chess piece is on.
    @param x The row index of the king.
    @param y The column index of the king.
*/

void King::Castling(Moveset & moves, const Board & board, const int &x, const int &y) const{
    if(m_Moved)
        return;
    if(board[x][0]->Type() == 'R' && !board[x][0]->GetMoved() && ClearPassage(board, x, 0, y) &&
       !board.Danger(x, y-2, m_White)) {
            moves.AddMove(x, y - 2);
    }
    if(board[x][7]->Type() == 'R' && !board[x][7]->GetMoved() && ClearPassage(board, x, 7, y) &&
       !board.Danger(x, y+2, m_White)) {
            moves.AddMove(x, y + 2);
    }
}

/**
    Checks if its possible for the king to move to a position.

    @param board The chessboard the chess piece is on.
    @param x The row index of the king.
    @param y The column index of the king.
    @param newx The row index of the position to be checked.
    @param newy The column index of the position to be checked.
    @param white The color of the king.
    @return Indicates if its possible for the king to move to the position.
*/

bool TryMove(const Board & board, const int &x, const int &y, const int &newx, const int &newy, bool white) {
    return (board[newx][newy]->Type() == 'E' || board[newx][newy]->IsWhite() != board[x][y]->IsWhite())
           && (!board.Danger(newx, newy, white));
}

/**
    Creates a collection of possible moves.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return A collection of the possible moves.
*/

Moveset King::GetMoves(const Board & board, const int &x, const int &y) const{
    Moveset moves;
    if(x < 7){
        if(TryMove(board, x, y, x+1, y, m_White))
                moves.AddMove(x+1, y);
        if(y < 7 && TryMove(board, x, y, x+1, y+1, m_White))
                moves.AddMove(x+1, y+1);
        if(y > 0 && TryMove(board, x, y, x+1, y-1, m_White))
                moves.AddMove(x+1, y-1);
    }
    if(x > 0){
        if(TryMove(board, x, y, x-1, y, m_White))
                moves.AddMove(x-1, y);
        if(y < 7 && TryMove(board, x, y, x-1, y+1, m_White))
                moves.AddMove(x-1, y+1);
        if(y > 0 && TryMove(board, x, y, x-1, y-1, m_White))
                moves.AddMove(x-1, y-1);
    }
    if(y < 7 && TryMove(board, x, y, x, y+1, m_White))
            moves.AddMove(x, y+1);
    if(y > 0 && TryMove(board, x, y, x, y-1, m_White))
            moves.AddMove(x, y-1);
    Castling(moves, board, x, y);
    return moves;
}