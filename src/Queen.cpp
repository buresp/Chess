//
// Created by petr on 8.5.17.
//

#include "Queen.h"
#include "Board.h"

Queen::Queen(bool w){
    m_White = w;
}
char Queen::Type()const{
    return 'Q';
}

bool Queen::IsWhite()const {
    return m_White;
}

Piece * Queen::Clone() const {
    return new Queen(m_White);
}

/**
    Check a direction for possible moves.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @param dirx The horizontal direction of the move.
    @param diry The vertical direction of the move.
*/

void Queen::TryDirection(Moveset & moves, const Board & board,
                         const int &x, const int &y, const int dirx, const int diry) {
    int addx = dirx;
    int addy = diry;
    while(x+addx <= 7 && y+addy <= 7 && x + addx >= 0 && y + addy >= 0){
        if(board[x+addx][y+addy]->Type() == 'E')
            moves.AddMove(x + addx, y+addy);
        if(board[x+addx][y+addy]->Type() != 'E' && board[x+addx][y+addy]->IsWhite() != board[x][y]->IsWhite()){
            moves.AddMove(x + addx, y+addy);
            break;
        }
        else if (board[x+addx][y+addy]->Type() != 'E')
            break;
        addx += dirx;
        addy += diry;
    }
}

/**
    Creates a collection of possible moves.

    @param board The chessboard the chess piece is on.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return A collection of the possible moves.
*/

Moveset Queen::GetMoves(const Board & board, const int &x, const int &y) const{
    Moveset moves;
    TryDirection(moves, board, x, y, 1, 1);
    TryDirection(moves, board, x, y, 1, -1);
    TryDirection(moves, board, x, y, -1, -1);
    TryDirection(moves, board, x, y, -1, 1);
    TryDirection(moves, board, x, y, 0, 1);
    TryDirection(moves, board, x, y, 0, -1);
    TryDirection(moves, board, x, y, 1, 0);
    TryDirection(moves, board, x, y, -1, 0);
    return moves;
}