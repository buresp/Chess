//
// Created by petr on 8.5.17.
//

#include "Empty.h"

Empty::Empty(){

}

char Empty::Type()const{
    return 'E';
}
bool Empty::IsWhite()const{
    return false;
}

Piece * Empty::Clone() const {
    return new Empty();
}

Moveset Empty::GetMoves(const Board & board,
                        const int &x, const int &y) const{
    return Moveset();
}
