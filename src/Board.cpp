//
// Created by petr on 8.5.17.
//

#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Empty.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <limits>
#include <iomanip>

Board::Board(){
    m_Board.resize(8);
}

Board::~Board() {
    for(size_t i = 0; i < m_Board.size(); ++i)
        for(size_t j = 0; j < m_Board[i].size(); ++j) {
            delete m_Board[i][j];
        }
}

Board::Board(const Board & obj){
    m_Board.resize(8);
    for(size_t i = 0; i < obj.m_Board.size(); ++i)
        for(size_t j = 0; j < obj.m_Board[i].size(); ++j) {
                m_Board[i].push_back(obj.m_Board[i][j]->Clone());
        }
}

/**
    Prints the state of the game.

    @param white Is true if it's the white player's turn, false otherwise.
*/

void Board::Print(bool white)const {
    for(size_t i = 0; i < m_Board.size(); ++i) {
        std::cout << "  ---------------------------------"<< std::endl;
        std::cout << m_Board.size()-i << " ";
        for (size_t j = 0; j < m_Board[i].size(); ++j)
        {
            if(m_Board[i][j]->Type() == 'E')
                std::cout << "|   ";
            else if(m_Board[i][j]->IsWhite())
                std::cout << "| " << m_Board[i][j]->Type() << ' ';
            else
                std::cout << "| " << (char)tolower(m_Board[i][j]->Type()) << ' ';
        }
        std::cout << '|';
        if(i == 3 && white)
            std::cout << "  White (uppercase) player's turn. Fitness: " << std::fixed << GetFitness();
        if(i == 3 && !white)
            std::cout << "  Black (lowercase) player's turn. Fitness: " << std::fixed << GetFitness();
        std::cout << std::endl;
    }
    std::cout << "  ---------------------------------"<< std::endl;
    std::cout << "    A   B   C   D   E   F   G   H"<< std::endl;
}

/**
    Saves the game state into a text file.

    @param fname The name of the save file.
    @param white Is true if it's the white player's turn, false otherwise.
    @return True if the game was saved successfully, false otherwise.
*/

bool Board::Save(std::string fname, bool white) const{
    mkdir("Saves", 0777);
    fname = "./Saves/" + fname + ".brd";
    std::ofstream myfile(fname);
    if(myfile.good()){
        if(white)
            myfile << "White" << '\n';
        else
            myfile << "Black" << '\n';
        for (size_t i = 0; i < m_Board.size(); ++i) {
            for (size_t j = 0; j < m_Board[i].size(); ++j) {
                if(m_Board[i][j]->IsWhite() || m_Board[i][j]->Type() == 'E') {
                    if (m_Board[i][j]->GetMoved())
                        myfile << 'm' << m_Board[i][j]->Type();
                    else
                        myfile << ' ' << m_Board[i][j]->Type();
                }
                else {
                    if (m_Board[i][j]->GetMoved())
                        myfile << 'm' << ((char) tolower(m_Board[i][j]->Type()));
                    else
                        myfile << ' ' << ((char) tolower(m_Board[i][j]->Type()));
                }
            }
            myfile << '\n';
        }
        if(myfile.good()) {
            myfile.close();
            std::cout << "Game saved." << std::endl;
            return true;
        }
    }
    std::cout << "There was an error while saving.";
    myfile.close();
    return false;
}

/**
    Returns a pointer to a chess piece based on the input.

    @param j The column index of the chess piece.
    @param line The line read from the file.
    @return The pointer to a chess piece.
*/

Piece * TellPiece(int j, std::string line){
    Piece * res;
    if (line[(j*2)+1] == 'E')
        res = new Empty();
    else if (line[(j*2)+1] == 'P')
        res = new Pawn(true);
    else if (line[(j*2)+1] == 'p')
        res = new Pawn(false);
    else if (line[(j*2)+1] == 'R')
        res = new Rook(true);
    else if (line[(j*2)+1] == 'r')
        res = new Rook(false);
    else if (line[(j*2)+1] == 'B')
        res = new Bishop(true);
    else if (line[(j*2)+1] == 'b')
        res = new Bishop(false);
    else if (line[(j*2)+1] == 'H')
        res = new Knight(true);
    else if (line[(j*2)+1] == 'h')
        res = new Knight(false);
    else if (line[(j*2)+1] == 'Q')
        res = new Queen(true);
    else if (line[(j*2)+1] == 'q')
        res = new Queen(false);
    else if (line[(j*2)+1] == 'K')
        res = new King(true);
    else if (line[(j*2)+1] == 'k')
        res = new King(false);
    if(line[j*2] == 'm')
        res->Moved();
    return res;
}

/**
    Loads the game state from a save file.

    @param fname The name of the save file.
    @param wturn Is true if it's the white player's turn, false otherwise.
    @return True if the game was loaded successfully, false otherwise.
*/

bool Board::Load(std::string fname, bool & wturn){
    fname = "./Saves/" + fname + ".brd";
    std::ifstream myfile(fname);
    std::string line;
    if(myfile.good()){
        std::getline(myfile, line);
        if(line == "White")
            wturn = true;
        else if(line == "Black")
            wturn = false;
        else
            return false;
        for (size_t i = 0; i < m_Board.size(); ++i) {
            std::getline(myfile, line);
            for (size_t j = 0; j < m_Board.size(); ++j) {
                if(line.size() == 16)
                    m_Board[i].push_back(TellPiece(j, line));
                else
                    return false;
            }
        }
        myfile.close();
        return myfile.good();
    }
    return false;
}

/**
    Sets up the game of chess.

    @param wturn Is true if it's the white player's turn, false otherwise.
*/

void Board::Setup(bool & wturn) {
    char c = ' ';
    while(c != 'N' && c != 'L') {
        std::cout << "To load a save file, type 'L', to play a new game, type 'N'." << '\n';
        std::cin >> c;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if(c == 'N'){
        m_Board[0].push_back(new Rook(false));
        m_Board[0].push_back(new Knight(false));
        m_Board[0].push_back(new Bishop(false));
        m_Board[0].push_back(new Queen(false));
        m_Board[0].push_back(new King(false));
        m_Board[0].push_back(new Bishop(false));
        m_Board[0].push_back(new Knight(false));
        m_Board[0].push_back(new Rook(false));
        for(size_t i = 0; i < m_Board.size(); ++i)
            m_Board[1].push_back(new Pawn(false));
        for(int i = 2; i < 6; ++i)
            for(size_t j = 0; j < m_Board.size(); ++j)
                m_Board[i].push_back(new Empty());
        for(size_t i = 0; i < m_Board.size(); ++i)
            m_Board[6].push_back(new Pawn(true));
        m_Board[7].push_back(new Rook(true));
        m_Board[7].push_back(new Knight(true));
        m_Board[7].push_back(new Bishop(true));
        m_Board[7].push_back(new Queen(true));
        m_Board[7].push_back(new King(true));
        m_Board[7].push_back(new Bishop(true));
        m_Board[7].push_back(new Knight(true));
        m_Board[7].push_back(new Rook(true));
    }
    else{
        while (true){
            std::cout << "Type the name of the save file." << '\n';
            std::string fname;
            std::cin >> fname;
            if(Load(fname, wturn))
                break;
        }
    }
}

/**
    Determines if the game is in a state of checkmate.

    @param white Is true if it's the white player's turn, false otherwise.
    @return True if the player on turn has no possible moves.
*/

bool Board::CheckMate(bool white) const{
    for (size_t i = 0; i < m_Board.size(); ++i)
        for (size_t j = 0; j < m_Board[i].size(); ++j) {
            if (m_Board[i][j]->Type() != 'E' && m_Board[i][j]->IsWhite() == white) {
                Moveset moves = m_Board[i][j]->GetMoves(*this,i, j);
                CheckMoves(moves, white, i, j);
                if(moves.Size() != 0)
                    return false;
            }
        }
    return true;
}

/**
    Starts the game.

    @param white The pointer to the white player.
    @param black The pointer to the black player.
    @param wturn Is true if it's the white player's turn, false otherwise.
*/

void Board::Start(Player * white, Player * black, bool wturn) {
    if(!wturn){
        if(CheckMate(false)){
            std::cout << "Checkmate, white player wins." << std::endl;
            return;
        }
        Print(false);
        black->Play(*this);
    }
    while(true) {
        Print(true);
        if(CheckMate(true)){
            std::cout << "Checkmate, black player wins." << std::endl;
            break;
        }
        white->Play(*this);
        if(CheckMate(false)){
            std::cout << "Checkmate, white player wins." << std::endl;
            break;
        }
        Print(false);
        black->Play(*this);
    }
}

/**
    Determines if the piece is endangered.

    @param x The row index of the chess piece being evaluated.
    @param y The column index of the chess piece being evaluated.
    @param white Is true if it's the white player's turn, false otherwise.
    @return True if the piece is endangered.
*/

bool Board::Danger(const int & x, const int & y, bool white) const{
    for(size_t i = 0; i < m_Board.size(); ++i)
        for(size_t j = 0; j < m_Board[i].size(); ++j){
            if(m_Board[i][j]->Type() == 'K')
                continue;
            if(m_Board[i][j]->IsWhite() != white && GetMoves(i, j).Contains(x, y) &&
                    !(m_Board[i][j]->Type() == 'P' && j == (size_t)y))
                return true;
        }
    if(white) {
        // Check if it is endangered by a black pawn.
        return (x > 0 && y > 0 && m_Board[x - 1][y - 1]->Type() == 'P' && !m_Board[x - 1][y - 1]->IsWhite()) ||
               (x > 0 && y < 7 && m_Board[x - 1][y + 1]->Type() == 'P' && !m_Board[x - 1][y + 1]->IsWhite());
    }
    else{
        // Checks if it is endangered by a white pawn.
        return (x < 7 && y > 0 && m_Board[x+1][y-1]->Type() == 'P' && m_Board[x+1][y-1]->IsWhite()) ||
               (x < 7 && y < 7 && m_Board[x+1][y+1]->Type() == 'P' && m_Board[x+1][y+1]->IsWhite());
    }
}

/**
    Moves the piece or pieces on the board.

    @param x The row index of the chess piece being moved.
    @param y The column index of the chess piece being moved.
    @param newx The row index of the chess piece's new position.
    @param newy The column index of the chess piece's new position.
*/

void Board::Move(const int & x, const int & y, const int & newx, const int & newy){
    // Checks if it is Castling move.
    if(m_Board[x][y]->Type() == 'K' && abs(newy - y) == 2){
        if(newy > y)
            Move(x, 7, x, newy - 1);
        if(newy < y)
            Move(x, 0, x, newy + 1);
    }
    delete m_Board[newx][newy];
    m_Board[newx][newy] = m_Board[x][y];
    m_Board[x][y] = new Empty();
    m_Board[newx][newy]->Moved();
}

/**
    Promotes a pawn based on the player's choice.

    @param x The row index of the chess piece being promoted.
    @param y The column index of the chess piece being promoted.
    @param c The piece it's being promoted to.
    @param white Is true if it's the white player's turn, false otherwise.
*/

void Board::Promote(const int & x, const int & y, const char & c, bool white){
    if(c == 'Q') {
        delete m_Board[x][y];
        m_Board[x][y] = new Queen(white);
    }
    if(c == 'B') {
        delete m_Board[x][y];
        m_Board[x][y] = new Bishop(white);
    }
    if(c == 'H') {
        delete m_Board[x][y];
        m_Board[x][y] = new Knight(white);
    }
    if(c == 'R') {
        delete m_Board[x][y];
        m_Board[x][y] = new Rook(white);
    }
    m_Board[x][y]->Moved();
}

/**
    Returns the position of a king.

    @param white Is true if it's the white player's king, false otherwise.
    @return The king's position.
*/

std::pair<int, int> Board::KingPos(bool white) const{
    for (size_t i = 0; i < m_Board.size(); ++i)
        for (size_t j = 0; j < m_Board[i].size(); ++j) {
            if(m_Board[i][j]->Type() == 'K' && m_Board[i][j]->IsWhite() == white)
                return std::pair<int, int>(i, j);
        }
    return std::pair<int, int>();
}

/**
    Checks if moving a piece will endanger the king. If it does, it removes it from the possible moves.

    @param moves The moves the piece can make.
    @param white Is true if it's the white player's turn, false otherwise.
    @param x The row index of the chess piece being moved.
    @param y The column index of the chess piece being moved.
*/

void Board::CheckMoves(Moveset & moves, bool white, const int & x, const int & y) const {
    for (int i = 0; i < (int)moves.Size(); ++i) {
        Board tmp = Board(*this);
        tmp.Move(x, y, moves[i].first, moves[i].second);
        std::pair<int, int> kingpos = tmp.KingPos(white);
        if(tmp.Danger(kingpos.first, kingpos.second, white)){
            moves.DelMove(i--);
        }
    }
}

/**
    Checks if a pawn is doubled.

    @param x The row index of the pawn.
    @param y The column index of the pawn.
    @return True if the pawn is doubled, false otherwise.
*/

bool Board::Doubled(const int & x, const int & y) const{
    return (x < 7 && m_Board[x+1][y]->IsWhite() == m_Board[x][y]->IsWhite() && m_Board[x+1][y]->Type() == 'P')
        || (x > 0 && m_Board[x-1][y]->IsWhite() == m_Board[x][y]->IsWhite() && m_Board[x-1][y]->Type() == 'P');
}


/**
    Checks if a piece is blocked (no possible moves).

    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return True if the piece is blocked, false otherwise.
*/

bool Board::Blocked(const int & x, const int & y) const{
    return m_Board[x][y]->GetMoves(*this, x, y).Size() == 0;
}

/**
    Checks if a pawn is isolated.

    @param x The row index of the pawn.
    @param y The column index of the pawn.
    @return True if the pawn is isolated, false otherwise.
*/

bool Board::Isolated(const int & x, const int & y) const{
    if(x > 0){
        if(m_Board[x-1][y]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x-1][y]->IsWhite())
            return false;
        if(y > 0 && m_Board[x-1][y-1]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x-1][y-1]->IsWhite())
            return false;
        if(y < 7 && m_Board[x-1][y+1]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x-1][y+1]->IsWhite())
            return false;
    }
    if(x < 7){
        if(m_Board[x+1][y]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x+1][y]->IsWhite())
            return false;
        if(y > 0 && m_Board[x+1][y-1]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x+1][y-1]->IsWhite())
            return false;
        if(y < 7 && m_Board[x+1][y+1]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x+1][y+1]->IsWhite())
            return false;
    }
    if(y > 0 && m_Board[x][y-1]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x][y-1]->IsWhite())
        return false;
    return !(y < 7 && m_Board[x][y+1]->Type() == 'P' && m_Board[x][y]->IsWhite() == m_Board[x][y+1]->IsWhite());
}

/**
    Evaluates the fitness of the board's state from the perspective of the white player. 
    (Based on https://chessprogramming.wikispaces.com/Evaluation)

    @return The fitness of the board.
*/

double Board::GetFitness() const{
    double f = 0, tmp = 0;
    for (size_t i = 0; i < m_Board.size(); ++i)
        for (size_t j = 0; j < m_Board[i].size(); ++j) {
            tmp = 0;
            if(m_Board[i][j]->Type() == 'K')
                tmp = 200;
            else if(m_Board[i][j]->Type() == 'Q')
                tmp = 9;
            else if(m_Board[i][j]->Type() == 'R')
                tmp = 5;
            else if(m_Board[i][j]->Type() == 'B' || m_Board[i][j]->Type() == 'H')
                tmp = 3;
            else if(m_Board[i][j]->Type() == 'P') {
                tmp = 1;
                if(Doubled(i, j) || Blocked(i, j) || Isolated(i, j))
                tmp = 0.5;
            }
            if(m_Board[i][j]->IsWhite()) {
                tmp += m_Board[i][j]->GetMoves(*this, i, j).Size() * 0.1;
                f += tmp;
            }
            else {
                tmp += m_Board[i][j]->GetMoves(*this, i, j).Size() * 0.1;
                f -= tmp;
            }
        }
    return f;
}