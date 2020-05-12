//
// Created by petr on 9.5.17.
//

#include <iostream>
#include <limits>
#include "Board.h"
#include "Human.h"

/**
    Clears the input buffer if the fail flag is set.

    @return Indicates if the clear was done.
*/

bool Clear(){
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
    return false;
}

/**
    Handles the promotion of the player's pawn.

    @param board The board being played on.
    @param x The row index.
    @param y The column index.
*/

void Human::Promotion(Board & board, const int &x, const int &y)const{
    if(board[x][y]->Type() == 'P' && (x == 7 || x == 0)){
        char c = ' ';
        while(c != 'Q' && c != 'B' && c != 'H' && c != 'R'){
            std::cout << "Which piece do you want to promote the pawn to? (Choose \"Q\",\"B\",\"H\" or \"R\")" << std::endl;
            std::cin >> c;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        board.Promote(x, y, c, board[x][y]->IsWhite());
    }
}

/**
    Asks the player what to do. Reads input and checks if it's possible to do.

    @param board The board being played on.
    @param legals The collection of selected chess piece's possible moves.
    @param x The row index.
    @param y The column index.
    @param white The player's color.
*/

void Ask(Board & board, Moveset & legals, int &x, int &y, bool white){
    char cfrom = ' ';
    int nfrom = 0;
    while (nfrom < 1 || nfrom > 8 || cfrom > 'H' || cfrom < 'A'
           || !white == board[8 - nfrom][cfrom - 'A']->IsWhite() || legals.Size() == 0) {
        std::cout << "Choose the piece you want to move (like 'A1'), to save, type 'S'." << std::endl;
        std::cin >> cfrom;
        if(cfrom == 'S'){
            std::string fname;
            std::cout << "Choose the save file name." << std::endl;
            std::cin >> fname;
            if(Clear())
                continue;
            board.Save(fname, white);
            continue;
        }
        std::cin >> nfrom;
        Clear();
        x = 8 - nfrom; y = cfrom - 'A';
        if(x >= 0 && x <= 7 && y >= 0 && y <= 7 ) {
            if(board[x][y]->IsWhite() != white){
                std::cout << "You can't move that piece." << std::endl;
                continue;
            }
            legals = board.GetMoves(x, y);
            board.CheckMoves(legals, white, x, y);
        }
        if(legals.Size() == 0)
            std::cout << "You can't move that piece." << std::endl;
    }
}

/**
    Executes the player's turn.

    @param board The chessboard being played on.
*/

void Human::Play(Board & board)const{
    // Character representing column index
    char cto = ' ';
    // Numbers representing row indexes
    int x = 0, y = 0, nto = 0;
    Moveset legals;
    Ask(board, legals, x, y, m_White);
    std::cout << "Possible Moves: ";
    legals.Print();
    while (true) {
        std::cout << "Choose your move (for example A1)" << std::endl;
        std::cin >> cto;
        std::cin >> nto;
        if (Clear())
            continue;
        int newx = 8 - nto, newy = cto - 'A';
        if(x == newx && y == newy)
            continue;
        if(legals.Contains(newx, newy)) {
            board.Move(x, y, newx, newy);
            Promotion(board, newx, newy);
            break;
        }
    }
}