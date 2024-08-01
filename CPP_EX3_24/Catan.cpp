#include "Catan.hpp"
#include <iostream>
#include <stdexcept>
#include <map>

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
        playTurn();
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

    bool Catan::canAfford(const Player& player, const std::map<ResourceType, int>& cost) const {
        for (const auto& item : cost) {
            if (player.getResourceCount(item.first) < item.second) {
                return false;
            }
        }
        return true;
    }

    void Catan::playTurn() {
        Player& player = getCurrentPlayer();
        std::string action;

        std::cout << "Player " << player.getName() << "'s turn." << std::endl;
        player.rollDice();

        while (true) {
            std::cout << "Enter action (build_road, build_settlement, build_city, buy_dev_card, trade, end_turn): ";
            std::cin >> action;

            try {
                if (action == "build_road") {
                    std::map<ResourceType, int> cost = {{ResourceType::Hills, 1}, {ResourceType::Forest, 1}};
                    if (canAfford(player, cost)) {
                        player.useResource(ResourceType::Hills, 1);
                        player.useResource(ResourceType::Forest, 1);
                        std::vector<std::string> places;
                        std::vector<int> placesNum;
                        std::string place;
                        int placeNum;

                        std::cout << "Enter road details (place name and place number): ";
                        std::cin >> place >> placeNum;
                        places.push_back(place);
                        placesNum.push_back(placeNum);

                        player.placeRoad(places, placesNum, gameBoard);
                        std::cout << "Road built successfully." << std::endl;
                    } else {
                        std::cout << "Not enough resources to build a road." << std::endl;
                    }
                } else if (action == "build_settlement") {
                    std::map<ResourceType, int> cost = {{ResourceType::Hills, 1}, {ResourceType::Forest, 1}, {ResourceType::Pasture, 1}, {ResourceType::Agricultural, 1}};
                    if (canAfford(player, cost)) {
                        player.useResource(ResourceType::Hills, 1);
                        player.useResource(ResourceType::Forest, 1);
                        player.useResource(ResourceType::Pasture, 1);
                        player.useResource(ResourceType::Agricultural, 1);
                        std::vector<std::string> places;
                        std::vector<int> placesNum;
                        std::string place;
                        int placeNum;

                        std::cout << "Enter settlement details (place name and place number): ";
                        std::cin >> place >> placeNum;
                        places.push_back(place);
                        placesNum.push_back(placeNum);

                        player.placeSettelemnt(places, placesNum, gameBoard);
                        std::cout << "Settlement built successfully." << std::endl;
                    } else {
                        std::cout << "Not enough resources to build a settlement." << std::endl;
                    }
                } else if (action == "build_city") {
                    std::map<ResourceType, int> cost = {{ResourceType::Mountains, 3}, {ResourceType::Agricultural, 2}};
                    if (canAfford(player, cost)) {
                        player.useResource(ResourceType::Mountains, 3);
                        player.useResource(ResourceType::Agricultural, 2);
                        std::vector<int> placesNum;
                        int placeNum1, placeNum2;

                        std::cout << "Enter city details (two place numbers): ";
                        std::cin >> placeNum1 >> placeNum2;
                        placesNum.push_back(placeNum1);
                        placesNum.push_back(placeNum2);

                        player.placeCity(placesNum, gameBoard);
                        std::cout << "City built successfully." << std::endl;
                    } else {
                        std::cout << "Not enough resources to build a city." << std::endl;
                    }
                } else if (action == "buy_dev_card") {
                    std::map<ResourceType, int> cost = {{ResourceType::Mountains, 1}, {ResourceType::Pasture, 1}, {ResourceType::Agricultural, 1}};
                    if (canAfford(player, cost)) {
                        player.useResource(ResourceType::Mountains, 1);
                        player.useResource(ResourceType::Pasture, 1);
                        player.useResource(ResourceType::Agricultural, 1);
                        player.buyDevelopmentCard();
                        std::cout << "Development card purchased successfully." << std::endl;
                    } else {
                        std::cout << "Not enough resources to buy a development card." << std::endl;
                    }
                } else if (action == "trade") {
                    std::string otherPlayerName, giveResource, getResource;
                    int giveAmount, getAmount;
                    std::cout << "Enter trade details (other player name, resource to give, amount, resource to get, amount): ";
                    std::cin >> otherPlayerName >> giveResource >> giveAmount >> getResource >> getAmount;

                    Player* otherPlayer = nullptr;
                    for (auto& p : players) {
                        if (p.getName() == otherPlayerName) {
                            otherPlayer = &p;
                            break;
                        }
                    }

                    if (otherPlayer) {
                        try {
                            player.trade(*otherPlayer, giveResource, getResource, giveAmount, getAmount);
                            std::cout << "Trade completed successfully." << std::endl;
                        } catch (const std::runtime_error& e) {
                            std::cout << e.what() << std::endl;
                        }
                    } else {
                        std::cout << "Player not found." << std::endl;
                    }
                } else if (action == "end_turn") {
                    break;
                } else {
                    std::cout << "Invalid action." << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            } catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
            }
        }

        nextTurn();
    }
}
