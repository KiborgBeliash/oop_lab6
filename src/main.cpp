#include <iostream>
#include <memory>
#include "battle.h"
#include "observer.h"
#include "npc_factory.h"  // Добавлен include!

void printMenu() {
    std::cout << "\n=== Dungeon Editor ===\n";
    std::cout << "1. Add NPC\n";
    std::cout << "2. Print all NPCs\n";
    std::cout << "3. Save to file\n";
    std::cout << "4. Load from file\n";
    std::cout << "5. Start battle\n";
    std::cout << "6. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    auto observable = std::make_shared<Observable>();
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>();
    
    observable->addObserver(consoleObserver);
    observable->addObserver(fileObserver);
    
    Battle battle(observable);
    
    int choice;
    do {
        printMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                std::cout << "NPC type (0=Dragon, 1=Toad, 2=Knight): ";
                int type;
                std::cin >> type;
                
                std::cout << "X coordinate (0-500): ";
                int x;
                std::cin >> x;
                
                std::cout << "Y coordinate (0-500): ";
                int y;
                std::cin >> y;
                
                std::cout << "Name: ";
                std::string name;
                std::cin.ignore();  // Очищаем буфер
                std::getline(std::cin, name);
                
                if (x < 0 || x > 500 || y < 0 || y > 500) {
                    std::cout << "Coordinates out of bounds!\n";
                    break;
                }
                
                try {
                    auto npc = NPCFactory::createNPC(static_cast<NPCType>(type), x, y, name);
                    battle.addNPC(npc);
                    std::cout << "NPC added successfully!\n";
                } catch (const std::exception& e) {
                    std::cout << "Error creating NPC: " << e.what() << std::endl;
                }
                break;
            }
            case 2:
                battle.printAllNPCs();
                break;
            case 3: {
                std::cout << "Filename: ";
                std::string filename;
                std::cin.ignore();
                std::getline(std::cin, filename);
                battle.saveToFile(filename);
                std::cout << "Saved!\n";
                break;
            }
            case 4: {
                std::cout << "Filename: ";
                std::string filename;
                std::cin.ignore();
                std::getline(std::cin, filename);
                battle.loadFromFile(filename);
                std::cout << "Loaded!\n";
                break;
            }
            case 5: {
                std::cout << "Battle range: ";
                int range;
                std::cin >> range;
                battle.fight(range);
                break;
            }
            case 6:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while(choice != 6);
    
    return 0;
}