#include "battle.h"
#include "npc_factory.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Battle::Battle(std::shared_ptr<Observable> observable) 
    : observable(observable), battleRange(0) {}

void Battle::addNPC(std::shared_ptr<NPC> npc) {
    npcs.push_back(npc);
}

void Battle::removeDeadNPCs() {
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
            [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); }),
        npcs.end()
    );
}

void Battle::printAllNPCs() const {
    std::cout << "\n=== NPC List ===\n";
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << npc->getTypeName() << " \"" << npc->getName() 
                      << "\" at (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }
    std::cout << "Total: " << npcs.size() << " NPCs\n";
}

void Battle::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    
    for (const auto& npc : npcs) {
        file << NPCFactory::saveToString(npc) << std::endl;
    }
    
    file.close();
}

void Battle::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    
    npcs.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                auto npc = NPCFactory::loadFromString(line);
                npcs.push_back(npc);
            } catch (const std::exception& e) {
                std::cerr << "Error loading NPC: " << e.what() << std::endl;
            }
        }
    }
    
    file.close();
}

void Battle::fight(int range) {
    battleRange = range;
    
    std::cout << "\n=== Battle Starting ===\n";
    observable->notifyObservers("Battle started with range " + std::to_string(range));
    
    for (size_t i = 0; i < npcs.size(); i++) {
        if (!npcs[i]->isAlive()) continue;
        
        for (size_t j = i + 1; j < npcs.size(); j++) {
            if (!npcs[j]->isAlive()) continue;
            
            if (npcs[i]->isClose(npcs[j], range)) {
                if (shouldFight(npcs[i], npcs[j])) {
                    // Attacker i attacks defender j
                    BattleVisitor visitor(npcs[i]);
                    npcs[j]->accept(visitor);
                    
                    if (visitor.getFightResult()) {
                        std::string message = npcs[i]->getName() + " (" + 
                                              npcs[i]->getTypeName() + 
                                              ") killed " + 
                                              npcs[j]->getName() + " (" + 
                                              npcs[j]->getTypeName() + ")";
                        observable->notifyObservers(message);
                        
                        // If attacker also died (e.g., toad vs toad)
                        if (!npcs[i]->isAlive()) {
                            message = npcs[j]->getName() + " (" + 
                                      npcs[j]->getTypeName() + 
                                      ") also died in battle";
                            observable->notifyObservers(message);
                        }
                    }
                }
            }
        }
    }
    
    removeDeadNPCs();
    std::cout << "\n=== Battle Ended ===\n";
    observable->notifyObservers("Battle ended. Remaining NPCs: " + std::to_string(npcs.size()));
}

bool Battle::shouldFight(std::shared_ptr<NPC> a, std::shared_ptr<NPC> b) {
    // Check if these NPC types should fight according to rules
    NPCType typeA = a->getType();
    NPCType typeB = b->getType();
    
    // Toad fights everyone (including other toads)
    if (typeA == NPCType::Toad || typeB == NPCType::Toad) {
        return true;
    }
    
    // Dragon vs Knight
    if ((typeA == NPCType::Dragon && typeB == NPCType::Knight) ||
        (typeA == NPCType::Knight && typeB == NPCType::Dragon)) {
        return true;
    }
    
    return false;
}