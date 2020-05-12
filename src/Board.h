//
// Created by petr on 8.5.17.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <string>
#include "Moveset.h"
#include "Player.h"
#include "Piece.h"

/**
    The implementation of the chessboard. The chessboard stores an array of all chess pieces.
*/
class Board{
public:
    Board();
    ~Board();

/**
    Constructs a deep copy of chessboard.

    @param obj The chess board to be copied.
*/
    Board(const Board & obj);

/**
    Prints the chessboard.

    @param white Indicates who plays next.
*/
    void Print(bool white) const;

/**
    Sets up the chessboard, can load a save from file or set up a new game.

    @param wturn Indicates who plays first.
*/
    void Setup(bool & wturn);

/**
    Saves the game into a file. Makes a /Saves directory if it doesn't exist.

    @param fname Name of the file.
    @param white Indicates which player plays next.
    @return Indicates if the game was saved successfully.
*/
    bool Save(std::string fname, bool white) const;

/**
    Loads the game from a file. Sets up the chessboard.

    @param fname Name of the file.
    @param wturn Indicates which player plays next.
    @return Indicates if the game was loaded successfully.
*/
    bool Load(std::string fname, bool & wturn);

/**
    Checks if a player is in a checkmate.

    @param white Indicates which player to check.
    @return Indicates if the player is in a checkmate.
*/
    bool CheckMate(bool white) const;

/**
    Starts the game.

    @param white The white player.
    @param black The black player.
    @param wturn Indicates who plays first.
*/
    void Start(Player * white, Player * black, bool wturn);

    inline const std::vector<Piece*> & operator[](const int & x) const { return m_Board[x]; }

/**
    Returns all possible moves of the chess piece.

    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
    @return Collection of all possible moves of the chess piece on position [x][y].
*/
    inline Moveset GetMoves(const int & x, const int & y) const { return m_Board[x][y]->GetMoves(*this, x, y); }

/**
    Executes a chess move.

    @param x The row index of the moving chess piece.
    @param y The column index of the moving chess piece.
    @param newx The row index to move the chess piece to.
    @param newy The column index to move the chess piece to.
*/
    void Move(const int & x, const int & y, const int & newx, const int & newy);

/**
    Promotes a pawn.

    @param x The row index of the pawn.
    @param y The column index of the pawn.
    @param c The character indicating what to promote the pawn to.
    @param white The pawn's color.
*/
    void Promote(const int & x, const int & y, const char & c, bool white);

/**
    Returns the position of the King.

    @param white The King's color.
    @return A pair of row (first) and column (second) indexes.
*/
    std::pair<int, int> KingPos(bool white) const;

/**
    Eliminates moves that would leave the King endangered.

    @param moves The collection of moves to check.
    @param white The chess piece's color.
    @param x The row index of the chess piece.
    @param y The column index of the chess piece.
*/
    void CheckMoves(Moveset & moves, bool white, const int & x, const int & y) const;

/**
    Checks if a position is dangerous for the player (endangered by an enemy's chess piece).

    @param x The row index of the position.
    @param y The column index of the position.
    @param white The color of the player checking if it is dangerous for him.
    @return Indicates if the position is endangered by a black chess piece.
*/
    bool Danger(const int & x, const int & y, bool white) const;

/**
    Checks if a pawn is doubled.

    @param x The row index of the pawn.
    @param y The column index of the pawn.
    @return Indicates if the pawn is doubled.
*/
    bool Doubled(const int & x, const int & y) const;

/**
    Checks if a pawn is blocked.

    @param x The row index of the pawn.
    @param y The column index of the pawn.
    @return Indicates if the pawn is blocked.
*/
    bool Blocked(const int & x, const int & y) const;

/**
    Checks if a pawn is isolated.

    @param x The row index of the pawn.
    @param y The column index of the pawn.
    @return Indicates if the pawn is isolated.
*/
    bool Isolated(const int & x, const int & y) const;

/**
    Calculates the fitness based on the chessboard's state. (The higher the better for the white player)

    @return The fitness.
*/
    double GetFitness() const;
private:
    std::vector<std::vector<Piece*>> m_Board;
};

#endif //CHESS_BOARD_H
