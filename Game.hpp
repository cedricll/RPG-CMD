#ifndef HW2_GAME_HPP
#define HW2_GAME_HPP

#include "Modes.hpp"
#include "State.hpp"
#include <memory>
#include <stack>
#include <unordered_map> 

class Game
{
    State state_;

 //    ModeType exploreMode = ModeType::Exploration;
	// ModeType inventoryMode = ModeType::Inventory;
	// ModeType fightMode = ModeType::Fighting;

	ExplorationMode explore;
	InventoryMode inventory;
	FightingMode fight;

	// std::unordered_map<ModeType, Mode> modeMap{ {exploreMode, explore}, 
	// 											{inventoryMode, inventory}, 
	// 											{fightMode, fight} };



	std::unordered_map<ModeType, Mode*> modeMap{ {ExplorationMode::T, &explore}, {InventoryMode::T, &inventory}, {FightingMode::T, &fight} };
	Mode* mode;

  public:
    Game(State &&state);

    void run();
};

#endif
