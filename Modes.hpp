#ifndef HW2_MODES_HPP
#define HW2_MODES_HPP

#include "State.hpp"
#include <string>
#include <vector>

enum class ModeType
{
    Exploration,
    Inventory,
    Fighting
};

enum CommandResult
{
    Success,
    SwitchExploration,
    SwitchInventory,
    SwitchFighting,
    Quit,
};

class Mode
{
  protected:
    // You want to have access to the state in this and all subclasses.
    State *state_{};

  public:
    virtual ~Mode() = default;
    virtual CommandResult handle_command(std::string cmd) = 0;

    CommandResult getHealth() { return this->health(); }
    CommandResult switchToInventory() {return this->inventory(); }
    CommandResult getHelp() { return this->help(); }
    CommandResult leave() { return this->exit(); }

    void setState(State *state);


  private:
    // add methods for commands health, inventory, help and exit.
    CommandResult health();
    CommandResult inventory(); // switches to inventory mode, but how??????????
    CommandResult help(); // how to list cmds????????????????????
    CommandResult exit(); // how to exit???????????????
    // add explore?
};

class ExplorationMode : public Mode
{
  public:
    static const ModeType T;

    // CommandResult goExplore() {return this->explore()}

    CommandResult handle_command(std::string cmd)
    {
      // std::cout << "Handling ex command: " << cmd << std::endl;

      if (cmd == "health")
      {
        return this->getHealth();
      }

      else if (cmd == "inventory")
      {
        return this->switchToInventory();
      }

      else if (cmd == "help")
      {
        return this->getHelp();
      }

      // else if (cmd == "exit")
      // {
      //   // quit the game
      // }

      else if (cmd == "explore") // IMPL
      {
        // fwd queue
        return this->explore();
      }

      // else
      // {
      //   // error message?
      // }

      //std::cout << "Invalid Command" << std::endl;
      return CommandResult::Success;
    }

  private:
    // add methods for command explore.
    CommandResult explore();
    // forward queue

};

class InventoryMode : public Mode
{
  public:
    static const ModeType T;
    CommandResult getHelp() { return this->help(); }
    // CommandResult closeInv() { return this->close(); }

    CommandResult handle_command(std::string cmd)
    {
      // std::cout << "Handling inv command: " << cmd << std::endl;

      if (cmd == "help")
      {
        return this->getHelp();
      }

      else if (cmd == "inventory")
      {
        return this->switchToInventory();
      }

      else if (cmd == "health")
      {
        return this->getHealth();
      }

      else if (cmd == "close")
      {
        return this->close();
      }

      else if (cmd == "list") 
      {
        return this->list();
      }

      else if (cmd == "equip")
      {
        return this->equip();
      }


      return CommandResult::Success;
    }

// Available commands: close, equip, exit, health, help, inventory, list

  private:
    // add methods for commands list, equip and close.
    CommandResult list();
    CommandResult equip();
    CommandResult close();
    CommandResult help();
};

class FightingMode : public Mode
{
  public:
    static const ModeType T;
    CommandResult getHelp() { return this->help(); }

    //Encounter encounter = this->state_->encounters.front(); // type encounter
    // this->state_->encounters.pop();

    CommandResult handle_command(std::string cmd)
    {
      // std::cout << "Handling fight command: " << cmd << std::endl;
      

      if (cmd == "help")
      {
        return this->getHelp();
      }

      else if (cmd == "attack")
      {
        return this->attack();
      }

      else if (cmd == "info")
      {
        return this->info();
      }

      return CommandResult::Success;
    }

  private:
    // add methods for commands info and attack.
    CommandResult info();
    CommandResult attack();
    CommandResult help();


};

#endif
