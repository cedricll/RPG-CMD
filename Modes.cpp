#include "Modes.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const ModeType ExplorationMode::T = ModeType::Exploration;
const ModeType InventoryMode::T = ModeType::Inventory;
const ModeType FightingMode::T = ModeType::Fighting;

CommandResult Mode::health()
{
	std::cout << "Health: " << this->state_->character.health.hitpoints << " / "
			  << this->state_->character.health.total_hitpoints << "." << std::endl << std::endl;
	return CommandResult::Success;
}

CommandResult Mode::inventory()
{
	std::cout << "Opened inventory." << std::endl << std::endl;
	// add Inventory mode type
	return CommandResult::SwitchInventory;
}

CommandResult Mode::help()
{
	// Available commands: exit, explore, health, help, inventory
	std::cout << "Available commands: exit, explore, health, help, inventory" << std::endl << std::endl;
	return CommandResult::Success;
}

CommandResult InventoryMode::help()
{
	std::cout << "Available commands: close, equip, exit, health, help, inventory, list" << std::endl << std::endl;
	return CommandResult::Success;
}

CommandResult FightingMode::help() 
{
	std::cout << "Available commands: attack, exit, health, help, info, inventory" << std::endl << std::endl;
	return CommandResult::Success;
}

CommandResult Mode::exit()
{
	return CommandResult::Quit;
}

CommandResult ExplorationMode::explore() // impl
{
	std::cout << "You wander through the wilderness until you suddenly encounter an enemy." << std::endl << std::endl;
	
	return CommandResult::SwitchFighting;
}

void Mode::setState(State *state)
{
	this->state_ = state;
}

CommandResult InventoryMode::close() 
{
	std::cout << "Closed inventory." << std::endl << std::endl;
	return CommandResult::SwitchExploration;
}

CommandResult InventoryMode::list()
{
	// this->state_->character.backpack // type Backpack

	for (long unsigned int i = 0; i < this->state_->character.backpack.items.size(); i++)
	{
		if (this->state_->character.backpack.items[i]->isArmor)
		{
			Armor *armor = (Armor*) this->state_->character.backpack.items[i];
			// std::cout << "It ran\n";
		//this->state_->character.backpack.items[i].name
			std::cout << "Item " << i + 1 << ": "  
					  << armor->name << ", " 
					  << "Armor, " << "defense " 
					  << armor->defense << std::endl;
		}

		else 
		{
			Weapon * weapon = (Weapon*) this->state_->character.backpack.items[i];
			std::cout << "Item " << i + 1 << ": "
					  << weapon->name << ", " 
					  << "Weapon, " << "damage " 
					  << weapon->damage << std::endl;
		}
	}

	std::cout << std::endl;

	return CommandResult::Success;
}

CommandResult InventoryMode::equip()
{
	int item_num;
	std::cout << "Enter item number:\n";
	std::cin >> item_num;


	// this->state_->character.backpack.add_item()
	if (this->state_->character.backpack.items[item_num - 1]->isArmor)
	{
		// std::cout << "This is armor\n" ;
		Armor *armor = (Armor*) this->state_->character.backpack.items[item_num - 1];
		this->state_->character.backpack.items.erase
						(this->state_->character.backpack.items.begin() + (item_num - 1) );
		this->state_->character.equip(armor);
	}

	else 
	{
		// std::cout << "This is weapon\n" ;
		Weapon *weapon = (Weapon*) this->state_->character.backpack.items[item_num - 1];
		this->state_->character.backpack.items.erase
						(this->state_->character.backpack.items.begin() + (item_num - 1) );
		this->state_->character.equip(weapon);
	}

	// auto item = this->state_->character.backpack.items[item_num - 1]; // Item *
	// this->state_->character.equip(item);

	std::cout << "Item equipped." << std::endl << std::endl;

	return CommandResult::Success;
	
}

CommandResult FightingMode::attack()
{
	// this->state_->encounters.front().enemy // enemy
	// this->state_->character // character

	// this->state_->character.weapon->damage // character damage
	// this->state_->encounters.front().enemy.damage // enemy damage
	// std::cout << "start of attack\n";
	int player_dealt = this->state_->character.weapon->damage;
	int player_armor = this->state_->character.armor->defense;
	int enemy_dealt = this->state_->encounters.front().enemy.damage;

	// std::cout << "init ints\n";

	int player_damaged = enemy_dealt - player_armor;

	if (enemy_dealt - player_armor < 0) 
	{
		player_damaged = 0;
	}

	// std::cout << "Player damaged\n";

	this->state_->encounters.front().enemy.health.hitpoints -= player_dealt;
	// std::cout << "Enemy hp go down\n";
	this->state_->character.health.hitpoints -= player_damaged;
	// std::cout << "player hp go down\n";

	if (this->state_->encounters.front().enemy.health.hitpoints <= 0)
	{
		// std::cout << "Enemy died\n";

		if (this->state_->encounters.size() == 1)
		{
			std::cout << "You won!" << std::endl;
			return CommandResult::Quit;
		}

		if ( this->state_->encounters.front().loot != nullptr && this->state_->encounters.front().loot->isArmor )
		{
			// std:: cout << "Got an armor\n";
			Armor *armor = (Armor*) this->state_->encounters.front().loot;
			this->state_->character.backpack.add_item(armor);
		}
		// this->state_->character.backpack.add_item(this->state_->encounters.front().loot);

		else if (this->state_->encounters.front().loot != nullptr)
		{
			// std::cout << "Got a weapon\n";
			Weapon *weapon = (Weapon*) this->state_->encounters.front().loot;
			this->state_->character.backpack.add_item(weapon);
		}

		
		std::cout << "You defeated the enemy!" << std::endl << std::endl;
		this->state_->encounters.pop();
		

		return CommandResult::SwitchExploration;
	}

	else if (this->state_->character.health.hitpoints <= 0)
	{
		std::cout << "You died!\n";
		return CommandResult::Quit;
	}

	std::cout << "You both attack. You dealt " << player_dealt << " damage and received "
			  << enemy_dealt << "-" << player_armor << "=" << player_damaged
			  << " damage." << std::endl << std::endl;

	
	// this->state_->encounters
	return CommandResult::Success;
}

CommandResult FightingMode::info()
{
	std::cout << "Enemy Health: " << this->state_->encounters.front().enemy.health.hitpoints
			  << std::endl << std::endl;

	return CommandResult::Success;
}