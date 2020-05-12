//
// Created by petr on 9.5.17.
//

#include "AI.h"
#include "Board.h"
#include <float.h>

// The size of the board
const int brdSize = 8;

/**
    Calculates the best fitness the player can achieve by moving the chess piece.

    @param board The chessboard being played on.
    @param x The row index of the chess piece being moved.
    @param y The column index of the chess piece being moved.
    @param best The best possible fitness yet.
    @param white The color of the player making the move.
*/

void Evaluate(Board & board, const int &x, const int &y, double & best, bool white){
    Moveset moves = board[x][y]->GetMoves(board, x, y);
    for (size_t k = 0; k < moves.Size(); ++k) {
        Board tmp = Board(board);
        tmp.Move(x, y, moves[k].first, moves[k].second);
        double movefit = tmp.GetFitness();
        if(white && movefit > best){
            best = movefit;
        }
        if(!white && movefit < best){
            best = movefit;
        }
    }
}

/**
    Determines which is the best move to do.

    @param board The chessboard being played on.
    @param x The row index of the chess piece being moved.
    @param y The column index of the chess piece being moved.
    @param best The best possible fitness yet.
    @param pos The position of the chess piece being moved by the best move.
    @param bestmove The position the chess piece will be moved to.
    @param white The color of the player making the move.
*/

void Step(Board & board, const int &x, const int &y, double & best,
          std::pair<int, int> &pos, std::pair<int, int> &bestmove, bool white){
    Moveset moves = board[x][y]->GetMoves(board, x, y);
    for (size_t k = 0; k < moves.Size(); ++k) {
        Board tmp = Board(board);
        tmp.Move(x, y, moves[k].first, moves[k].second);
        double sbest;
        if(white)
            sbest = DBL_MAX;
        else
            sbest = -DBL_MAX;
        for (int i = 0; i < brdSize; ++i)
            for (int j = 0; j < brdSize; ++j)
                if(!white == tmp[i][j]->IsWhite())
                    Evaluate(tmp, i, j, sbest, !white);
        if(white && sbest > best){
            best = sbest;
            pos.first = x;
            pos.second = y;
            bestmove.first = moves[k].first;
            bestmove.second = moves[k].second;
        }
        if(!white && sbest < best){
            best = sbest;
            pos.first = x;
            pos.second = y;
            bestmove.first = moves[k].first;
            bestmove.second = moves[k].second;
        }
    }
}

/**
    Executes the AI's turn.

    @param board The chessboard being played on.
*/

void AI::Play(Board & board)const{
    double best;
    std::pair<int, int> pos;
    std::pair<int, int> bestmove;
    if(m_White)
        best = -DBL_MAX;
    else
        best = DBL_MAX;
    for (int i = 0; i < brdSize; ++i)
        for (int j = 0; j < brdSize; ++j)
            if(m_White == board[i][j]->IsWhite())
                Step(board, i, j, best, pos, bestmove, m_White);

    board.Move(pos.first, pos.second, bestmove.first, bestmove.second);
    // Promotes a pawn to queen if it moved on the last row
    if(board[bestmove.first][bestmove.second]->Type() == 'P' && (bestmove.first == 7 || bestmove.first == 0))
        board.Promote(bestmove.first, bestmove.second, 'Q', board[bestmove.first][bestmove.second]->IsWhite());
}