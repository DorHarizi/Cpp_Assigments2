#include "DevelopmentCardType.hpp"

namespace ariel {
    DevelopmentCardType stringToDevelopmentCardType(const std::string& developmentCardType) {
        if (developmentCardType == "Monopoly") return DevelopmentCardType::Monopoly;
        if (developmentCardType == "Road Building") return DevelopmentCardType::RoadBuilding;
        if (developmentCardType == "Knight") return DevelopmentCardType::Knight;
        if (developmentCardType == "Largest Army") return DevelopmentCardType::LargestArmy;
        if (developmentCardType == "Victory Point") return DevelopmentCardType::VictoryPoint;
        throw std::invalid_argument("Invalid Development Card Type: " + developmentCardType);
    }

    std::string developmentCardTypeToString(const DevelopmentCardType& developmentCardType) {
        switch (developmentCardType) {
            case DevelopmentCardType::Monopoly: return "Monopoly";
            case DevelopmentCardType::RoadBuilding: return "Road Building";
            case DevelopmentCardType::Knight: return "Knight";
            case DevelopmentCardType::LargestArmy: return "Largest Army";
            case DevelopmentCardType::VictoryPoint: return "Victory Point";
            default: throw std::invalid_argument("Invalid Development Card Type");
        }
    }
}
