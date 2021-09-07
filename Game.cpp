#include "Game.hpp"
#include <iostream>
#include <string>

Game::Game(State &&state)
{
	// this->state_ = state;
	this->state_ = std::move(state);
	// this->mode = new ExplorationMode;
	this->mode = modeMap[ExplorationMode::T];
	this->mode->setState(&this->state_);
}

void Game::run()
{
	// ?

	std::string name;
	std::cout << "Please enter a name:\n";
	std::cin >> name;
	// std::cout << std::endl;
	std::cout << "Let the adventure begin, " << name << "!" <<std::endl << std::endl;

	this->state_.character.name = name;

	// std::cout << this->state_.character.name << std::endl;
	// modeMap[exlploreMode];

	std::string cmd;
	while (cmd != "exit")
	{
		std::cout << "Enter command (or help):\n";
		std::cin >> cmd;
		CommandResult cmd_res = this->mode->handle_command(cmd); // add a cmd here

		if (cmd_res == CommandResult::SwitchInventory)
		{
			// std::cout << "Mode switched to: Inv" << std::endl;
			this->mode = modeMap[InventoryMode::T];
			this->mode->setState(&this->state_); // may error
		}

		else if (cmd_res == CommandResult::SwitchFighting)
		{
			// std::cout << "Mode switched to: fight" << std::endl;
			this->mode = modeMap[FightingMode::T];
			this->mode->setState(&this->state_); // may error
		}

		else if (cmd_res == CommandResult::SwitchExploration)
		{
			// std::cout << "Mode switched to: expl" << std::endl;
			this->mode = modeMap[ExplorationMode::T];
			this->mode->setState(&this->state_); // may error
		}

		else if (cmd_res == CommandResult::Quit)
		{
			//game over
			break;
		}

		// if (cmd == "help")
		// {
		// 	std::cout << "Available commands: ";
		// }
	}
}
