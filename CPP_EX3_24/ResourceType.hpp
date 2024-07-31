#pragma once

#include <string>
#include <stdexcept>

/**
 * Resource and Yield types for the Catan game.
 * 
 * This header defines the ResourceType and YieldType enums and provides utility 
 * functions to convert between strings and these types. Each ResourceType corresponds 
 * to a specific YieldType, representing the resources produced by different types of land.
 */

namespace ariel {
    enum class ResourceType {
        Forest,         // ResourceType Forest
        Hills,          // ResourceType Hills
        Pasture,        // ResourceType Pasture Land
        Agricultural,   // ResourceType Agricultural Land
        Mountains,      // ResourceType Mountains
        Desert,         // ResourceType Desert
        None            // ResourceType None for default
    };

    enum class YieldType {
        wood,   // ResourceType Forest yields wood
        bricks, // ResourceType Hills yields bricks
        wool,   // ResourceType Pasture yields wool
        oats,   // ResourceType Agricultural yields oats
        iron,   // ResourceType Mountains yields iron
        None    // ResourceType Desert yields None
    };

    ResourceType stringToResourceType(const std::string& resourceType);
    YieldType stringToYieldType(const std::string& yieldType);
    std::string resourceTypeToString(const ResourceType resourceType);
    std::string yieldTypeToString(const YieldType yieldType);
    YieldType resourceTypeToYieldType(const ResourceType& resourceType);
}
