#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "ResourceType.hpp"

/**
 * The game consists of a board containing 19 plots of land surrounded by the sea. 
 * Every piece of land gives some resource (except the desert). 
 * The plots of land in the game are:
 *     1. Forest (4 pieces) -> yields wood.
 *     2. Hills (3 pieces) -> yields bricks.
 *     3. Pasture land (4 pieces) -> yields wool.
 *     4. Agricultural land (4 pieces) -> yields oats.
 *     5. Mountains (3 pieces) -> yields iron.
 *     6. Desert (1 piece) -> yields nothing.
 * All parts of the map are given some number between 2 and 12.
 * 
 * Board class for the Catan game.
 * 
 * This class represents the game board, which consists of 19 plots of land.
 * Each plot can be assigned a resource type and a yield type. The Board class 
 * provides functionality to randomly distribute resources and numbers to the 
 * plots or set them up manually. It also includes methods to retrieve the 
 * current state of the board and print the board for debugging or display purposes.
 * 
 * Public Methods:
 * - Board(): Constructor to initialize the board with default values.
 * - ~Board(): Destructor (no dynamic memory allocation, so no specific cleanup needed).
 * - void distributeResources(): Randomly distribute resources and numbers to the plots.
 * - void setupManualBoard(const std::vector<std::pair<int, std::pair<ResourceType, YieldType>>>& manualSetup): 
 *   Set up the board manually with specified resources and numbers.
 * - std::vector<std::pair<int, std::pair<ResourceType, YieldType>>> getLandPlots() const: 
 *   Get the current state of the land plots on the board.
 * - void printBoard() const: Print the current state of the board.
 * - void addPlayerSettlement(const std::string& player, int x, int y): Add a settlement for a player.
 * - void addPlayerRoad(const std::string& player, int x, int y): Add a road for a player.
 * - void addPlayerCity(const std::string& player, int x, int y): Add a city for a player.
 * - std::unordered_map<std::string, std::vector<std::pair<int, int>>> getPlayerSettlements() const: Get the current player settlements.
 * - std::unordered_map<std::string, std::vector<std::pair<int, int>>> getPlayerRoads() const: Get the current player roads.
 * - std::unordered_map<std::string, std::vector<std::pair<int, int>>> getPlayerCities() const: Get the current player cities.
 */

namespace ariel {

    class Board {
    private:
        std::vector<std::pair<int, std::pair<ResourceType, YieldType>>> landPlots;
        std::unordered_map<std::string, std::vector<std::pair<int, int>>> settlements;
        std::unordered_map<std::string, std::vector<std::pair<int, int>>> roads;
        std::unordered_map<std::string, std::vector<std::pair<int, int>>> cities;

    public:
        Board();
        ~Board() {} // No dynamic memory allocation, so nothing specific to clean up

        void distributeResources();
        void setupManualBoard(const std::vector<std::pair<int, std::pair<ResourceType, YieldType>>>& manualSetup);

        std::vector<std::pair<int, std::pair<ResourceType, YieldType>>> getLandPlots() const;
        void printBoard() const;

        void addPlayerSettlement(const std::string& player, int x, int y);
        void addPlayerRoad(const std::string& player, int x, int y);
        void addPlayerCity(const std::string& player, int x, int y);
        std::unordered_map<std::string, std::vector<std::pair<int, int>>> getPlayerSettlements() const;
        std::unordered_map<std::string, std::vector<std::pair<int, int>>> getPlayerRoads() const;
        std::unordered_map<std::string, std::vector<std::pair<int, int>>> getPlayerCities() const;
    };
}
