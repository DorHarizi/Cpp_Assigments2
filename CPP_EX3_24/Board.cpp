#include "Board.hpp"
#include <algorithm> // for std::shuffle
#include <random> // for std::random_device and std::mt19937
#include <iostream>

namespace ariel {

    Board::Board() {
        landPlots.resize(19, {0, {ResourceType::None, YieldType::None}}); // Initialize with 19 empty plots
    }

    void Board::distributeResources() {
        std::vector<std::pair<ResourceType, YieldType>> resources = {
            {ResourceType::Forest, YieldType::wood}, {ResourceType::Forest, YieldType::wood}, 
            {ResourceType::Forest, YieldType::wood}, {ResourceType::Forest, YieldType::wood},
            {ResourceType::Hills, YieldType::bricks}, {ResourceType::Hills, YieldType::bricks}, 
            {ResourceType::Hills, YieldType::bricks},
            {ResourceType::Pasture, YieldType::wool}, {ResourceType::Pasture, YieldType::wool}, 
            {ResourceType::Pasture, YieldType::wool}, {ResourceType::Pasture, YieldType::wool},
            {ResourceType::Agricultural, YieldType::oats}, {ResourceType::Agricultural, YieldType::oats}, 
            {ResourceType::Agricultural, YieldType::oats}, {ResourceType::Agricultural, YieldType::oats},
            {ResourceType::Mountains, YieldType::iron}, {ResourceType::Mountains, YieldType::iron}, 
            {ResourceType::Mountains, YieldType::iron},
            {ResourceType::Desert, YieldType::None} // Desert
        };

        std::vector<int> numbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12};
        std::vector<int> allNumbers;

        // Fill allNumbers to have 19 numbers between 2 and 12, excluding 7
        for (size_t i = 0; i < resources.size() - 1; ++i) {
            allNumbers.push_back(numbers[i % numbers.size()]);
        }
        allNumbers.push_back(7); // Ensure 7 is included for the desert

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(resources.begin(), resources.end(), g);
        std::shuffle(allNumbers.begin(), allNumbers.end(), g);

        for (size_t i = 0; i < landPlots.size(); ++i) {
            landPlots[i] = {allNumbers[i], resources[i]};
        }
    }

    void Board::setupManualBoard(const std::vector<std::pair<int, std::pair<ResourceType, YieldType>>>& manualSetup) {
        if (manualSetup.size() != 19) {
            throw std::invalid_argument("Manual setup must contain exactly 19 plots.");
        }
        landPlots = manualSetup;
    }

    std::vector<std::pair<int, std::pair<ResourceType, YieldType>>> Board::getLandPlots() const {
        return landPlots;
    }

    void Board::printBoard() const {
        std::cout << "-----------Current Board-----------" << std::endl;
        for (const auto& plot : landPlots) {
            std::cout << "Number: " << plot.first << " - Resource: " 
                      << resourceTypeToString(plot.second.first) << " (" 
                      << yieldTypeToString(plot.second.second) << ")" << std::endl;
        }
    }
}
