#ifndef VISITOR_H
#define VISITOR_H

#include <memory>  // для std::shared_ptr
#include "npc.h"   // для NPC и его наследников

// Предварительное объявление
class Dragon;
class Toad;
class Knight;

class NPCVisitor {
public:
    virtual ~NPCVisitor() = default;
    virtual void visit(Dragon& dragon) = 0;
    virtual void visit(Toad& toad) = 0;
    virtual void visit(Knight& knight) = 0;
};

class BattleVisitor : public NPCVisitor {
private:
    std::shared_ptr<NPC> attacker;
    bool fightResult;
    
public:
    BattleVisitor(std::shared_ptr<NPC> attacker);
    void visit(Dragon& dragon) override;
    void visit(Toad& toad) override;
    void visit(Knight& knight) override;
    
    bool getFightResult() const;
};

#endif // VISITOR_H