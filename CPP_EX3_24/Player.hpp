#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>
#include "ResourceType.hpp"
#include "DevelopmentCardType.hpp"
#include "Board.hpp"

/**
 * Player class for the Catan game.
 * 
 * This class represents a player in the game, managing their resources,
 * development cards, points, and game actions. The player can perform 
 * various actions such as placing settlements, roads, and cities, rolling 
 * dice, trading resources, buying development cards, and ending their turn.
 */

namespace ariel {

    class Player {
    private:
        std::string name; // Player's name
        int points; // Player's points in the game
        bool hasLargestArmy; // Whether the player has the largest army
        int knightCount; // Number of knights the player has
        static int totalKnights; // For tracking the largest army across all players
        std::map<ResourceType, int> resources; // Resources the player holds
        std::vector<DevelopmentCardType> developmentCards; // Development cards the player holds
        std::vector<std::pair<int, int>> roads; // Roads the player has placed
        std::vector<std::pair<int, int>> cities; // Cities the player has placed
        std::vector<std::pair<int, int>> settlements; // Settlements the player has placed

    public:
        Player(const std::string& name);
        ~Player(); // Destructor

        void placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void placeCity(const std::vector<std::pair<int, int>>& cityLocations);
        void rollDice();
        void trade(Player& other, const std::string& giveResource, const std::string& getResource, int giveAmount, int getAmount);
        void buyDevelopmentCard();
        void endTurn();
        void printPoints() const;
        void print() const;
        void addResource(ResourceType resource, int amount);
        void useResource(ResourceType resource, int amount);
        int getResourceCount(ResourceType resource) const;

        int getPoints() const; // Add this method
        std::string getName() const; // Add this method
    };
}
