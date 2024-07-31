#include "Catan.hpp"
#include <iostream>

namespace ariel {

    Catan::Catan(Player& player1, Player& player2, Player& player3) {
        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        currentPlayerIndex = 0;
    }

    Board Catan::getBoard() const {
        return gameBoard;
    }

    void Catan::ChooseStartingPlayer() {
        std::cout << "Starting player: " << players[0].getName() << std::endl;
        std::cout << std::endl;
    }

    Player& Catan::getCurrentPlayer() {
        return players[currentPlayerIndex];
    }

    void Catan::nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    void Catan::printWinner() const {
        const Player* winner = nullptr;
        for (const auto& player : players) {
            if (player.getPoints() >= 10) {
                winner = &player;
                break;
            }
        }
        if (winner) {
            std::cout << "Winner: " << winner->getName() << std::endl;
        } else {
            std::cout << "No winner yet." << std::endl;
        }
    }
}
