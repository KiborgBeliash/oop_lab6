#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include <memory>
#include <string>
#include "npc.h"  // ИСПРАВЛЕНО: было "npc_factory.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(NPCType type, int x, int y, const std::string& name);
    static std::shared_ptr<NPC> loadFromString(const std::string& data);
    static std::string saveToString(const std::shared_ptr<NPC>& npc);
    
private:
    static NPCType stringToType(const std::string& typeStr);
    static std::string typeToString(NPCType type);
};

#endif // NPC_FACTORY_H