#include "visitor.h"

BattleVisitor::BattleVisitor(std::shared_ptr<NPC> attacker) 
    : attacker(attacker), fightResult(false) {}

void BattleVisitor::visit(Dragon& dragon) {
    if (!attacker) return;
    
    switch(attacker->getType()) {
        case NPCType::Toad:
            // Toad eats everyone
            dragon.markDead();
            fightResult = true;
            break;
        case NPCType::Knight:
            // Knight kills Dragon
            dragon.markDead();
            fightResult = true;
            break;
        case NPCType::Dragon:
            // Dragons don't fight each other
            fightResult = false;
            break;
        default:
            fightResult = false;
    }
}

void BattleVisitor::visit(Toad& toad) {
    if (!attacker) return;
    
    switch(attacker->getType()) {
        case NPCType::Toad:
            // Toads eat each other too
            toad.markDead();
            attacker->markDead(); // Both die
            fightResult = true;
            break;
        case NPCType::Dragon:
        case NPCType::Knight:
            // Toad eats everyone
            toad.markDead();
            fightResult = true;
            break;
        default:
            fightResult = false;
    }
}

void BattleVisitor::visit(Knight& knight) {
    if (!attacker) return;
    
    switch(attacker->getType()) {
        case NPCType::Toad:
            // Toad eats everyone
            knight.markDead();
            fightResult = true;
            break;
        case NPCType::Dragon:
            // Dragon kills Knight
            knight.markDead();
            fightResult = true;
            break;
        case NPCType::Knight:
            // Knights don't fight each other
            fightResult = false;
            break;
        default:
            fightResult = false;
    }
}

bool BattleVisitor::getFightResult() const {
    return fightResult;
}