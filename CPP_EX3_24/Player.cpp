#include "Player.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm> // for std::find

namespace ariel {

    int Player::totalKnights = 0;

    Player::Player(const std::string& name) : name(name), points(0), hasLargestArmy(false), knightCount(0) {
        resources[ResourceType::Forest] = std::vector<int>();
        resources[ResourceType::Hills] = std::vector<int>();
        resources[ResourceType::Pasture] = std::vector<int>();
        resources[ResourceType::Agricultural] = std::vector<int>();
        resources[ResourceType::Mountains] = std::vector<int>();

        yieldTypePoints[YieldType::wood] = 0;
        yieldTypePoints[YieldType::bricks] = 0;
        yieldTypePoints[YieldType::wool] = 0;
        yieldTypePoints[YieldType::oats] = 0;
        yieldTypePoints[YieldType::iron] = 0;
    }

    Player::~Player() {}

    int Player::getPoints() const {
        return points;
    }

    std::string Player::getName() const {
        return name;
    }

    bool Player::isLocationOwnedByOthers(std::vector<int> placesNum, const Board& board) {
        auto allSettlements = board.getPlayerSettlements();
        auto allCities = board.getPlayerCities();
        auto allRoads = board.getPlayerRoads();

        for (const auto& player : allSettlements) {
            if (player.first != name) {
                for (const auto& settlement : player.second) {
                    if ((settlement.first == placesNum[0] && settlement.second == placesNum[1]) ||
                        (settlement.first == placesNum[0] && settlement.second == placesNum[1])) {
                        return true;
                    }
                }
            }
        }

        for (const auto& player : allCities) {
            if (player.first != name) {
                for (const auto& city : player.second) {
                    if (city.first == placesNum[0] || city.first == placesNum[1] || 
                        city.second == placesNum[0] || city.second == placesNum[1]) {
                        return true;
                    }
                }
            }
        }

        for (const auto& player : allRoads) {
            if (player.first != name) {
                for (const auto& road : player.second) {
                    if ((road.first == placesNum[0] && road.second == placesNum[1]) || 
                        (road.first == placesNum[1] && road.second == placesNum[0])) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void Player::placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
        if (places.size() != placesNum.size()) {
            throw std::invalid_argument("Places and placesNum vectors must have the same size.");
        }

        // Check if the player's roads are less than 2
        if (board.getPlayerRoads()[name].size() < 2) {
            if (isLocationOwnedByOthers(placesNum, board)) {
                throw std::invalid_argument("Cannot place road at plot number " + std::to_string(placesNum[0]) + ", " + std::to_string(placesNum[1]) + " because another player owns this location.");
            }
            board.addPlayerRoad(name, placesNum[0], placesNum[1]);
            return;
        }

        bool isConnected = false;

        // Check connection to settlements
        auto playerSettlements = board.getPlayerSettlements();
        if (playerSettlements.find(name) != playerSettlements.end()) {
            for (const auto& settlement : playerSettlements[name]) {
                if (settlement.first == placesNum[0] || settlement.first == placesNum[1] ||
                    settlement.second == placesNum[0] || settlement.second == placesNum[1]) {
                    isConnected = true;
                    break;
                }
            }
        }

        // Check connection to cities
        if (!isConnected) {
            auto playerCities = board.getPlayerCities();
            if (playerCities.find(name) != playerCities.end()) {
                for (const auto& city : playerCities[name]) {
                    if (city.first == placesNum[0] || city.first == placesNum[1] || 
                        city.second == placesNum[0] || city.second == placesNum[1]) {
                        isConnected = true;
                        break;
                    }
                }
            }
        }

        // Check connection to roads
        if (!isConnected) {
            auto playerRoads = board.getPlayerRoads();
            if (playerRoads.find(name) != playerRoads.end()) {
                for (const auto& road : playerRoads[name]) {
                    if (road.first == placesNum[0] + 1 || road.first == placesNum[1] - 1 || 
                        road.second == placesNum[0] + 1 || road.second == placesNum[1] - 1) {
                        isConnected = true;
                        break;
                    }
                }
            }
        }

        if (!isConnected) {
            throw std::invalid_argument("Cannot place road at plot number " + std::to_string(placesNum[0]) + ", " + std::to_string(placesNum[1]) + " because it is not connected to an existing settlement, city, or road.");
        }

        // If legal, add the road
        board.addPlayerRoad(name, placesNum[0], placesNum[1]);
    }

    void Player::placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
        if (places.size() != placesNum.size()) {
            throw std::invalid_argument("Places and placesNum vectors must have the same size.");
        }

        // Check if the place is connected to a road
        bool isConnectedToRoad = false;
        auto playerRoads = board.getPlayerRoads();
        if (playerRoads.find(name) != playerRoads.end()) {
            for (const auto& road : playerRoads[name]) {
                if (road.first == placesNum[0] || road.first == placesNum[1] || 
                    road.second == placesNum[0] || road.second == placesNum[1]) {
                    isConnectedToRoad = true;
                    break;
                }
            }
        }

        if (!isConnectedToRoad) {
            throw std::invalid_argument("Cannot place settlement at plot number " + std::to_string(placesNum[0]) + ", " + std::to_string(placesNum[1]) + " because it is not connected to an existing road.");
        }

        // Check distance from player's own settlements
        bool isFarEnoughFromOtherSettlements = true;
        auto playerSettlements = board.getPlayerSettlements();
        if (playerSettlements.find(name) != playerSettlements.end()) {
            for (const auto& settlement : playerSettlements[name]) {
                if (std::abs(settlement.first - placesNum[0]) < 2 && std::abs(settlement.second - placesNum[1]) < 2) {
                    isFarEnoughFromOtherSettlements = false;
                    break;
                }
            }
        }

        if (!isFarEnoughFromOtherSettlements) {
            throw std::invalid_argument("Cannot place settlement at plot number " + std::to_string(placesNum[0]) + ", " + std::to_string(placesNum[1]) + " because it is too close to another settlement.");
        }

        // If all checks pass, place the settlements
        for (size_t i = 0; i < places.size(); ++i) {
            int plotNumber = placesNum[i];
            // Update the resources field
            ResourceType resourceType = stringToResourceType(places[i]);
            resources[resourceType].push_back(plotNumber);

            // Update the yield type points
            auto yieldType = resourceTypeToYieldType(resourceType);
            yieldTypePoints[yieldType]++;
        }

        // Add the settlement to the board and update points
        board.addPlayerSettlement(name, placesNum[0], placesNum[1]);
        points += 1;
    }


    void Player::placeCity(const std::vector<int>& placesNum, Board& board) {
        if (placesNum.size() != 2) {
            throw std::invalid_argument("placesNum must contain exactly 2 elements.");
        }

        auto playerSettlements = board.getPlayerSettlements();
        bool hasSettlement = false;

        // Check if the player has a settlement at this placeNum
        if (playerSettlements.find(name) != playerSettlements.end()) {
            auto& settlements = playerSettlements[name];
            auto it = std::find_if(settlements.begin(), settlements.end(),
                                   [&placesNum](const std::pair<int, int>& settlement) {
                                       return (settlement.first == placesNum[0] && settlement.second == placesNum[1]) ||
                                              (settlement.first == placesNum[1] && settlement.second == placesNum[0]);
                                   });

            if (it != settlements.end()) {
                hasSettlement = true;
                settlements.erase(it); // Remove the settlement
            }
        }

        if (!hasSettlement) {
            throw std::invalid_argument("Cannot place city at plot numbers (" + std::to_string(placesNum[0]) + ", " + std::to_string(placesNum[1]) + ") because there is no settlement to upgrade.");
        }

        // Add the city
        board.addPlayerCity(name, placesNum[0], placesNum[1]);

        // Update points
        points += 1; 
    }

    void Player::rollDice() {
        int diceResult = rand() % 12 + 1;
        std::cout << name << " rolled a " << diceResult << std::endl;

        // Iterate through the player's resources
        for (auto& resourcePair : resources) {
            ResourceType resourceType = resourcePair.first;
            std::vector<int>& resourceLocations = resourcePair.second;

            // Check if the player's resources contain the diceResult
            if (std::find(resourceLocations.begin(), resourceLocations.end(), diceResult) != resourceLocations.end()) {
                // Update the corresponding yieldTypePoints
                YieldType yieldType = resourceTypeToYieldType(resourceType);
                yieldTypePoints[yieldType] += 1;
                std::cout << "Added 1 to " << yieldTypeToString(yieldType) << " points." << std::endl;
            }
        }
    }


    void Player::trade(Player& other, const std::string& giveResource, const std::string& getResource, int giveAmount, int getAmount) {
        ResourceType giveRes = stringToResourceType(giveResource);
        ResourceType getRes = stringToResourceType(getResource);

        if (resources[giveRes].size() >= static_cast<size_t>(giveAmount) && other.resources[getRes].size() >= static_cast<size_t>(getAmount)) {
            resources[giveRes].resize(resources[giveRes].size() - giveAmount);
            other.resources[getRes].resize(other.resources[getRes].size() - getAmount);
            resources[getRes].insert(resources[getRes].end(), getAmount, 0);  // Add received resources
            other.resources[giveRes].insert(other.resources[giveRes].end(), giveAmount, 0);  // Add given resources to other player

            // Update yield type points
            auto giveYieldType = resourceTypeToYieldType(giveRes);
            auto getYieldType = resourceTypeToYieldType(getRes);
            yieldTypePoints[giveYieldType] -= giveAmount;
            other.yieldTypePoints[getYieldType] -= getAmount;
            yieldTypePoints[getYieldType] += getAmount;
            other.yieldTypePoints[giveYieldType] += giveAmount;
        } else {
            throw std::runtime_error("Not enough resources for trade");
        }
    }

    void Player::buyDevelopmentCard() {
        if (resources[ResourceType::Mountains].size() >= 1 && resources[ResourceType::Pasture].size() >= 1 && resources[ResourceType::Agricultural].size() >= 1) {
            useResource(ResourceType::Mountains, 1);
            useResource(ResourceType::Pasture, 1);
            useResource(ResourceType::Agricultural, 1);
            DevelopmentCardType card = DevelopmentCardType::VictoryPoint;
            developmentCards.push_back(card);
            if (card == DevelopmentCardType::VictoryPoint) {
                points += 1;
            }
        } else {
            throw std::runtime_error("Not enough resources to buy a development card");
        }
    }

    void Player::endTurn() {
        std::cout << name << " has ended their turn." << std::endl;

        if (knightCount > 2 && !hasLargestArmy) {
            hasLargestArmy = true;
            points += 2;
            std::cout << name << " has acquired the largest army and earned 2 points!" << std::endl;
        }
    }

    void Player::printPoints() const {
        std::cout << name << " has " << points << " points." << std::endl;
    }

    void Player::print(const Board& board) const {
        std::cout << "Player: " << name << std::endl;
        std::cout << "Points: " << points << std::endl;
        
        std::cout << "Resources:" << std::endl;
        for (const auto& resource : resources) {
            std::cout << "  - " << resourceTypeToString(resource.first) << ": " << resource.second.size() << std::endl;
        }
        
        std::cout << "Development Cards:" << std::endl;
        for (const auto& card : developmentCards) {
            std::cout << "  - " << developmentCardTypeToString(card) << std::endl;
        }
        
        std::cout << "Yield Type Points:" << std::endl;
        for (const auto& yield : yieldTypePoints) {
            std::cout << "  - " << yieldTypeToString(yield.first) << ": " << yield.second << std::endl;
        }
        
        std::cout << "Roads:" << std::endl;
        auto playerRoads = board.getPlayerRoads();
        if (playerRoads.find(name) != playerRoads.end()) {
            for (const auto& road : playerRoads[name]) {
                std::cout << "  - (" << road.first << ", " << road.second << ")" << std::endl;
            }
        }

        std::cout << "Settlements:" << std::endl;
        auto playerSettlements = board.getPlayerSettlements();
        if (playerSettlements.find(name) != playerSettlements.end()) {
            for (const auto& settlement : playerSettlements[name]) {
                std::cout << "  - (" << settlement.first << ", " << settlement.second << ")" << std::endl;
            }
        }

        std::cout << "Cities:" << std::endl;
        auto playerCities = board.getPlayerCities();
        if (playerCities.find(name) != playerCities.end()) {
            for (const auto& city : playerCities[name]) {
                std::cout << "  - (" << city.first << ", " << city.second << ")" << std::endl;
            }
        }
        
        std::cout << "Has Largest Army: " << (hasLargestArmy ? "Yes" : "No") << std::endl;
        std::cout << "Knight Count: " << knightCount << std::endl;
    }

    void Player::addResource(ResourceType resource, int amount) {
        resources[resource].insert(resources[resource].end(), amount, 0);
        
        // Update yield type points
        auto yieldType = resourceTypeToYieldType(resource);
        yieldTypePoints[yieldType] += amount;
    }

    void Player::useResource(ResourceType resource, int amount) {
        if (resources[resource].size() < static_cast<size_t>(amount)) {
            throw std::runtime_error("Not enough resources");
        }
        resources[resource].resize(resources[resource].size() - amount);

        // Update yield type points
        auto yieldType = resourceTypeToYieldType(resource);
        yieldTypePoints[yieldType] -= amount;
    }

    int Player::getResourceCount(ResourceType resource) const {
        return static_cast<int>(resources.at(resource).size());
    }
}