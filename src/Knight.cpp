//
// Created by petr on 8.5.17.
//

#include "Knight.h"
#include "Board.h"

Knight::Knight(bool w){
    m_White = w;
}
char Knight::Type()const{
    return 'H';
}

bool Knight::IsWhite()const {
    return m_White;
}

Piece * Knight::Clone() const {
    return new Knight(m_White);
}

/**
    Creates a collection of possible moves.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return A collection of the possible moves.
*/

Moveset Knight::GetMoves(const Board & board, const int &x, const int &y) const{
    Moveset moves;
    if(x > 1 && y > 0 && (board[x-2][y-1]->Type() == 'E' || board[x-2][y-1]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x-2, y-1);
    if(x > 1 && y < 7 && (board[x-2][y+1]->Type() == 'E' || board[x-2][y+1]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x-2, y+1);
    if(x < 6 && y > 0 && (board[x+2][y-1]->Type() == 'E' || board[x+2][y-1]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x+2, y-1);
    if(x < 6 && y < 7 && (board[x+2][y+1]->Type() == 'E' || board[x+2][y+1]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x+2, y+1);

    if(x > 0 && y > 1 && (board[x-1][y-2]->Type() == 'E' || board[x-1][y-2]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x-1, y-2);
    if(x > 0 && y < 6 && (board[x-1][y+2]->Type() == 'E' || board[x-1][y+2]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x-1, y+2);
    if(x < 7 && y < 6 && (board[x+1][y+2]->Type() == 'E' || board[x+1][y+2]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x+1, y+2);
    if(x < 7 && y > 1 && (board[x+1][y-2]->Type() == 'E' || board[x+1][y-2]->IsWhite() != board[x][y]->IsWhite()))
        moves.AddMove(x+1, y-2);
    return moves;
}
