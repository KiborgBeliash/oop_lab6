#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>

enum class NPCType {
    Dragon,
    Toad,
    Knight
};

class NPCVisitor;

class NPC {
protected:
    int x, y;
    std::string name;
    NPCType type;
    bool alive;
    
public:
    NPC(int x, int y, const std::string& name, NPCType type);
    virtual ~NPC() = default;
    
    virtual void accept(NPCVisitor& visitor) = 0;
    
    int getX() const;
    int getY() const;
    std::string getName() const;
    NPCType getType() const;
    bool isAlive() const;
    void markDead();
    
    bool isClose(const std::shared_ptr<NPC>& other, int distance) const;
    virtual std::string getTypeName() const;
};

class Dragon : public NPC {
public:
    Dragon(int x, int y, const std::string& name);
    void accept(NPCVisitor& visitor) override;
    std::string getTypeName() const override;
};

class Toad : public NPC {
public:
    Toad(int x, int y, const std::string& name);
    void accept(NPCVisitor& visitor) override;
    std::string getTypeName() const override;
};

class Knight : public NPC {
public:
    Knight(int x, int y, const std::string& name);
    void accept(NPCVisitor& visitor) override;
    std::string getTypeName() const override;
};

#endif