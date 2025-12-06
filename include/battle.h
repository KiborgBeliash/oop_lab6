#ifndef BATTLE_H
#define BATTLE_H

#include <vector>
#include <memory>
#include <string>
#include "npc.h"
#include "observer.h"

class Battle {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::shared_ptr<Observable> observable;
    int battleRange;
    
public:
    Battle(std::shared_ptr<Observable> observable);
    
    void addNPC(std::shared_ptr<NPC> npc);
    void removeDeadNPCs();
    void printAllNPCs() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void fight(int range);
    
private:
    bool shouldFight(std::shared_ptr<NPC> a, std::shared_ptr<NPC> b);
};

#endif