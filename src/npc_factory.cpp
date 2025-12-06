#include "npc_factory.h"
#include <sstream>
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::createNPC(NPCType type, int x, int y, const std::string& name) {
    switch(type) {
        case NPCType::Dragon:
            return std::make_shared<Dragon>(x, y, name);
        case NPCType::Toad:
            return std::make_shared<Toad>(x, y, name);
        case NPCType::Knight:
            return std::make_shared<Knight>(x, y, name);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}

std::shared_ptr<NPC> NPCFactory::loadFromString(const std::string& data) {
    std::istringstream iss(data);
    std::string typeStr, name;
    int x, y;
    
    if (!(iss >> typeStr >> x >> y)) {
        throw std::runtime_error("Invalid data format");
    }
    
    std::getline(iss >> std::ws, name);
    
    NPCType type = stringToType(typeStr);
    return createNPC(type, x, y, name);
}

std::string NPCFactory::saveToString(const std::shared_ptr<NPC>& npc) {
    if (!npc) return "";
    
    std::ostringstream oss;
    oss << typeToString(npc->getType()) << " "
        << npc->getX() << " " << npc->getY() << " "
        << npc->getName();
    return oss.str();
}

NPCType NPCFactory::stringToType(const std::string& typeStr) {
    if (typeStr == "Dragon") return NPCType::Dragon;
    if (typeStr == "Toad") return NPCType::Toad;
    if (typeStr == "Knight") return NPCType::Knight;
    throw std::invalid_argument("Unknown NPC type string: " + typeStr);
}

std::string NPCFactory::typeToString(NPCType type) {
    switch(type) {
        case NPCType::Dragon: return "Dragon";
        case NPCType::Toad: return "Toad";
        case NPCType::Knight: return "Knight";
        default: return "Unknown";
    }
}