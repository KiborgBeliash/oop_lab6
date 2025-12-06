#include <gtest/gtest.h>
#include "npc.h"
#include "npc_factory.h"
#include "visitor.h"

TEST(NPCTest, Creation) {
    auto dragon = NPCFactory::createNPC(NPCType::Dragon, 100, 200, "Smaug");
    EXPECT_EQ(dragon->getType(), NPCType::Dragon);
    EXPECT_EQ(dragon->getName(), "Smaug");
    EXPECT_TRUE(dragon->isAlive());
}

TEST(NPCTest, DistanceCheck) {
    auto npc1 = NPCFactory::createNPC(NPCType::Knight, 0, 0, "Arthur");
    auto npc2 = NPCFactory::createNPC(NPCType::Dragon, 3, 4, "Draco");
    
    EXPECT_TRUE(npc1->isClose(npc2, 10));
    EXPECT_FALSE(npc1->isClose(npc2, 4));
}

TEST(NPCTest, BattleRules) {
    auto toad = NPCFactory::createNPC(NPCType::Toad, 0, 0, "Toady");
    auto dragon = NPCFactory::createNPC(NPCType::Dragon, 1, 1, "Draco");
    auto knight = NPCFactory::createNPC(NPCType::Knight, 2, 2, "Arthur");
    
    // Toad should kill dragon
    BattleVisitor visitor1(toad);
    dragon->accept(visitor1);
    EXPECT_TRUE(visitor1.getFightResult());
    EXPECT_FALSE(dragon->isAlive());
    
    // Reset
    dragon->markDead();
    
    // Knight should kill dragon
    BattleVisitor visitor2(knight);
    dragon->accept(visitor2);
    EXPECT_TRUE(visitor2.getFightResult());
}