#include "ResourceType.hpp"

namespace ariel {
    ResourceType stringToResourceType(const std::string& resourceType) {
        if (resourceType == "Forest") return ResourceType::Forest;
        if (resourceType == "Hills") return ResourceType::Hills;
        if (resourceType == "Pasture Land") return ResourceType::Pasture;
        if (resourceType == "Agricultural Land") return ResourceType::Agricultural;
        if (resourceType == "Mountains") return ResourceType::Mountains;
        if (resourceType == "Desert") return ResourceType::Desert;
        throw std::invalid_argument("Invalid Resource Type: " + resourceType);
    }

    YieldType stringToYieldType(const std::string& yieldType) {
        if (yieldType == "wood") return YieldType::wood;
        if (yieldType == "bricks") return YieldType::bricks;
        if (yieldType == "wool") return YieldType::wool;
        if (yieldType == "oats") return YieldType::oats;
        if (yieldType == "iron") return YieldType::iron;
        throw std::invalid_argument("Invalid Yield Type: " + yieldType);
    }

    YieldType resourceTypeToYieldType(const ResourceType& resourceType){
        if (resourceType == ResourceType::Forest) return YieldType::wood;
        if (resourceType == ResourceType::Hills) return YieldType::bricks;
        if (resourceType == ResourceType::Pasture) return YieldType::wool;
        if (resourceType == ResourceType::Agricultural) return YieldType::oats;
        if (resourceType == ResourceType::Mountains) return YieldType::iron;
        if (resourceType == ResourceType::Desert || resourceType == ResourceType::None) return YieldType::None;
        throw std::invalid_argument("Invalid Resource Type");
    }

    std::string resourceTypeToString(const ResourceType resourceType) {
        switch (resourceType) {
            case ResourceType::Forest: return "Forest";
            case ResourceType::Hills: return "Hills";
            case ResourceType::Pasture: return "Pasture Land";
            case ResourceType::Agricultural: return "Agricultural Land";
            case ResourceType::Mountains: return "Mountains";
            case ResourceType::Desert: return "Desert";
            case ResourceType::None: return "None";
            default: throw std::invalid_argument("Invalid Resource Type");
        }
    }

    std::string yieldTypeToString(const YieldType yieldType) {
        switch (yieldType) {
            case YieldType::wood: return "wood";
            case YieldType::bricks: return "bricks";
            case YieldType::wool: return "wool";
            case YieldType::oats: return "oats";
            case YieldType::iron: return "iron";
            case YieldType::None: return "None";
            default: throw std::invalid_argument("Invalid Yield Type");
        }
    }
}
