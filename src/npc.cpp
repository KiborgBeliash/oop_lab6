#include "npc.h"
#include "visitor.h"
#include <cmath>

// NPC base class
NPC::NPC(int x, int y, const std::string& name, NPCType type) 
    : x(x), y(y), name(name), type(type), alive(true) {}

int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
std::string NPC::getName() const { return name; }
NPCType NPC::getType() const { return type; }
bool NPC::isAlive() const { return alive; }
void NPC::markDead() { alive = false; }

bool NPC::isClose(const std::shared_ptr<NPC>& other, int distance) const {
    if (!other || !other->isAlive() || !alive) return false;
    
    int dx = x - other->getX();
    int dy = y - other->getY();
    return std::sqrt(dx*dx + dy*dy) <= distance;
}

std::string NPC::getTypeName() const {
    switch(type) {
        case NPCType::Dragon: return "Dragon";
        case NPCType::Toad: return "Toad";
        case NPCType::Knight: return "Knight";
        default: return "Unknown";
    }
}

// Dragon
Dragon::Dragon(int x, int y, const std::string& name) 
    : NPC(x, y, name, NPCType::Dragon) {}

void Dragon::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Dragon::getTypeName() const {
    return "Dragon";
}

// Toad
Toad::Toad(int x, int y, const std::string& name) 
    : NPC(x, y, name, NPCType::Toad) {}

void Toad::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Toad::getTypeName() const {
    return "Toad";
}

// Knight
Knight::Knight(int x, int y, const std::string& name) 
    : NPC(x, y, name, NPCType::Knight) {}

void Knight::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Knight::getTypeName() const {
    return "Knight";
}