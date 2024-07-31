#pragma once

#include <vector>
#include <string>
#include "Player.hpp"
#include "Board.hpp"

/**
 * Catan class for the Catan game.
 * 
 * This class manages the overall game, including players and the game board. 
 * It provides functionality to start the game, choose the starting player, 
 * move to the next player's turn, and print the winner.
 */

namespace ariel {

    class Catan {
    private:
        std::vector<Player> players; // List of players in the game
        Board gameBoard; // The game board
        int currentPlayerIndex; // Index of the current player

    public:
        Catan(Player& player1, Player& player2, Player& player3);

        Board getBoard() const;
        void ChooseStartingPlayer();
        Player& getCurrentPlayer();
        void nextTurn();
        void printWinner() const;
    };
}
