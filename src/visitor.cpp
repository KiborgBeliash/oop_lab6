#include "visitor.h"

BattleVisitor::BattleVisitor(std::shared_ptr<NPC> attacker) 
    : attacker(attacker), fightResult(false) {}

void BattleVisitor::visit(Dragon& dragon) {
    if (!attacker) return;
    
    switch(attacker->getType()) {
        case NPCType::Toad:
            dragon.markDead();
            fightResult = true;
            break;
        case NPCType::Knight:
            dragon.markDead();
            fightResult = true;
            break;
        case NPCType::Dragon:
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
            toad.markDead();
            attacker->markDead();
            fightResult = true;
            break;
        case NPCType::Dragon:
        case NPCType::Knight:
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
            knight.markDead();
            fightResult = true;
            break;
        case NPCType::Dragon:
            knight.markDead();
            fightResult = true;
            break;
        case NPCType::Knight:
            fightResult = false;
            break;
        default:
            fightResult = false;
    }
}

bool BattleVisitor::getFightResult() const {
    return fightResult;
}