//
// Created by petr on 16.5.17.
//

#include <iostream>
#include "Moveset.h"

void Moveset::AddMove(const int & x, const int & y){
    m_Moves.push_back(std::pair<int, int>(x, y));
}

void Moveset::Print() const{
    if(m_Moves.size() == 0)
        return;
    for(size_t i = 0; i < m_Moves.size()-1; ++i)
        std::cout << (char)('A' + m_Moves[i].second) << 8 - m_Moves[i].first << ", ";
    if(m_Moves.size() != 0)
        std::cout << (char)('A' + m_Moves[m_Moves.size()-1].second) << 8 - m_Moves[m_Moves.size()-1].first << std::endl;
}

bool Moveset::Contains(const int & x, const int & y) const{
    for(auto & a : m_Moves)
        if(a.first == x && a.second == y)
            return true;
    return false;
}