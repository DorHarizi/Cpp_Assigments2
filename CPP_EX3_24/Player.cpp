#include "Player.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm> // for std::find

namespace ariel {

    int Player::totalKnights = 0;

    Player::Player(const std::string& name) : name(name), points(0), hasLargestArmy(false), knightCount(0) {
        resources[ResourceType::Forest] = 0;
        resources[ResourceType::Hills] = 0;
        resources[ResourceType::Pasture] = 0;
        resources[ResourceType::Agricultural] = 0;
        resources[ResourceType::Mountains] = 0;
        resources[ResourceType::Desert] = 0;
    }

    Player::~Player() {}

    void Player::placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
        if (places.size() != placesNum.size()) {
            throw std::invalid_argument("Places and placesNum vectors must have the same size.");
        }

        for (size_t i = 0; i < places.size(); ++i) {
            int plotNumber = placesNum[i];

            auto landPlots = board.getLandPlots();
            auto it = std::find_if(landPlots.begin(), landPlots.end(), [plotNumber](const std::pair<int, std::pair<ResourceType, YieldType>>& plot) {
                return plot.first == plotNumber;
            });

            if (it == landPlots.end()) {
                throw std::invalid_argument("Invalid plot number: " + std::to_string(plotNumber));
            }

            ResourceType resourceType = stringToResourceType(places[i]);

            if (it->second.first == ResourceType::None) {
                resources[resourceType] += 1;
                settlements.push_back({plotNumber, plotNumber});
            } else if (it->second.first == resourceType) {
                resources[resourceType] += 1;
                settlements.push_back({plotNumber, plotNumber});
            } else {
                throw std::invalid_argument("Plot number " + std::to_string(plotNumber) + " is already occupied by a different resource.");
            }
        }
        points += 1;
    }

    void Player::placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
        if (places.size() != placesNum.size()) {
            throw std::invalid_argument("Places and placesNum vectors must have the same size.");
        }

        for (size_t i = 0; i < places.size(); ++i) {
            int plotNumber = placesNum[i];

            auto landPlots = board.getLandPlots();
            auto it = std::find_if(landPlots.begin(), landPlots.end(), [plotNumber](const std::pair<int, std::pair<ResourceType, YieldType>>& plot) {
                return plot.first == plotNumber;
            });

            if (it == landPlots.end()) {
                throw std::invalid_argument("Invalid plot number: " + std::to_string(plotNumber));
            }

            roads.push_back({plotNumber, placesNum[(i + 1) % placesNum.size()]});
        }
    }

    void Player::placeCity(const std::vector<std::pair<int, int>>& cityLocations) {
        for (const auto& location : cityLocations) {
            if (std::find(cities.begin(), cities.end(), location) != cities.end()) {
                throw std::invalid_argument("City already exists at plot number (" + std::to_string(location.first) + ", " + std::to_string(location.second) + ")");
            }

            cities.push_back(location);
            points += 2;
        }
    }

    void Player::rollDice() {
        int diceResult = rand() % 12 + 1;
        std::cout << name << " rolled a " << diceResult << std::endl;
    }

    void Player::trade(Player& other, const std::string& giveResource, const std::string& getResource, int giveAmount, int getAmount) {
        ResourceType giveRes = stringToResourceType(giveResource);
        ResourceType getRes = stringToResourceType(getResource);

        if (resources[giveRes] >= giveAmount && other.resources[getRes] >= getAmount) {
            resources[giveRes] -= giveAmount;
            other.resources[getRes] -= getAmount;
            resources[getRes] += getAmount;
            other.resources[giveRes] += giveAmount;
        } else {
            throw std::runtime_error("Not enough resources for trade");
        }
    }

    void Player::buyDevelopmentCard() {
        if (resources[ResourceType::Mountains] >= 1 && resources[ResourceType::Pasture] >= 1 && resources[ResourceType::Agricultural] >= 1) {
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

    void Player::print() const {
        std::cout << "Player: " << name << std::endl;
        std::cout << "Points: " << points << std::endl;
        std::cout << "Resources:" << std::endl;
        for (const auto& resource : resources) {
            std::cout << "  - " << resourceTypeToString(resource.first) << ": " << resource.second << std::endl;
        }
        std::cout << "Development Cards:" << std::endl;
        for (const auto& card : developmentCards) {
            std::cout << "  - " << developmentCardTypeToString(card) << std::endl;
        }
        std::cout << "Has Largest Army: " << (hasLargestArmy ? "Yes" : "No") << std::endl;
        std::cout << "Knight Count: " << knightCount << std::endl;
        std::cout << "Roads:" << std::endl;
        for (const auto& road : roads) {
            std::cout << "  - (" << std::get<0>(road) << ", " << std::get<1>(road) << ")" << std::endl;
        }
        std::cout << "Cities:" << std::endl;
        for (const auto& city : cities) {
            std::cout << "  - (" << std::get<0>(city) << ", " << std::get<1>(city) << ")" << std::endl;
        }
        std::cout << "Settlements:" << std::endl;
        for (const auto& settlement : settlements) {
            std::cout << "  - (" << std::get<0>(settlement) << ", " << std::get<1>(settlement) << ")" << std::endl;
        }
        std::cout << std::endl;
    }

    void Player::addResource(ResourceType resource, int amount) {
        resources[resource] += amount;
    }

    void Player::useResource(ResourceType resource, int amount) {
        if (resources[resource] < amount) {
            throw std::runtime_error("Not enough resources");
        }
        resources[resource] -= amount;
    }

    int Player::getResourceCount(ResourceType resource) const {
        return resources.at(resource);
    }

    int Player::getPoints() const {
        return points;
    }

    std::string Player::getName() const {
        return name;
    }
}
