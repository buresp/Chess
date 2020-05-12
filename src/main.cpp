//
// Created by petr on 8.5.17.
//

#include <iostream>
#include <limits>
#include "Board.h"
#include "Human.h"
#include "AI.h"

// Starting point of the program
int main() {
    int players = 0;
    // Ask if player wants to play against AI or a second player
    while(players != 1 && players != 2)
    {
        std::cout << "For single player, type \"1\", for 2 players, type \"2\"." << std::endl;
        std::cin >> players;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    Board board;
    bool wturn = true;
    board.Setup(wturn);
    // Start the game
    if(players == 1)
        board.Start(new Human(true), new AI(false), wturn);
    else
        board.Start(new Human(true), new Human(false), wturn);
    return 0;
}