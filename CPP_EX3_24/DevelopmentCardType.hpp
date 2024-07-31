#pragma once

#include <string>
#include <stdexcept> 

/**
 * Development card types for the Catan game.
 * 
 * This header defines the DevelopmentCardType enum and provides utility functions 
 * to convert between strings and this type. Development cards include various 
 * types such as Monopoly, RoadBuilding, Knight, LargestArmy, and VictoryPoint.
 */

namespace ariel {
    enum class DevelopmentCardType {
        Monopoly, 
        RoadBuilding, 
        Knight,
        LargestArmy,
        VictoryPoint
    };

    DevelopmentCardType stringToDevelopmentCardType(const std::string& developmentCardType);
    std::string developmentCardTypeToString(const DevelopmentCardType& developmentCardType);
}
