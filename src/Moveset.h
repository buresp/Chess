//
// Created by petr on 16.5.17.
//

#ifndef CHESS_MOVESET_H
#define CHESS_MOVESET_H

#include <vector>

/**
    The implementation of a Moveset. It stores the possible moves of a chess piece.
*/

class Moveset{
public:
    Moveset(){}

/**
    Adds a position to the vector.

    @param x The row index of the position.
    @param y The column index of the position.
*/
    void AddMove(const int & x, const int & y);

/**
    Prints all possible moves.
*/
    void Print() const;

/**
    Returns the size of the vector.

    @return The size of the vector.
*/
    inline unsigned long Size() const { return m_Moves.size(); }

    inline const std::pair<int, int> operator[](const int & x) const { return m_Moves[x]; };

/**
    Deletes the i-th element in the vector.

    @param i The index of the element to erase.
*/
    inline void DelMove(int i){ m_Moves.erase(m_Moves.begin() + i); }

/**
    Determines if the position is already in the vector.

    @param x The row index of the position.
    @param y The column index of the position.
*/
    bool Contains(const int & x, const int & y) const;
private:
    std::vector<std::pair<int, int>> m_Moves;
};

#endif //CHESS_MOVESET_H
