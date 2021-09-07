#ifndef HW2_ENTITIES_HPP
#define HW2_ENTITIES_HPP

#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>

// TODO: add constructors and helper methods you need (you are free to modify all entities as you see fit)

// Any type of item that can be rewarded by completing encounters.
struct Item // Abstract class, use Item as pointer 
{
    std::string name;
    // int defense;
    // int damage;
    bool isArmor = true;

    explicit Item(const std::string &name) : name(name)
    {

    }

    // always define a virtual deconstructor in base classes
    virtual ~Item() = default;
};

// An armor that reduces damage caused by enemies.
struct Armor : public Item
{
    // Subtract this from incoming damage to the player if equipped.
    int defense;
    // bool isArmor() { return true; }

    Armor(const std::string &name, int defense) : Item(name), defense(defense)
    {

    }
};

// A weapon which causes damage to enemies.
struct Weapon : public Item
{
    // Damage dealt on attacking an enemy.
    // bool isArmor = false;
    int damage;
    // bool isArmor() { return false; }

    Weapon(const std::string &name, int damage) : Item(name), damage(damage)
    {
        isArmor = false;
    }
};

// The health of a character or enemy.
struct Health
{
    // Current hitpoints of character or enemy.
    int hitpoints;
    // Total hitpoints of character or enemy.
    int total_hitpoints;

    // Initialize hitpoints and total_hitpoints to the same value, because a character or enemy always starts with full
    // hitpoints.
    explicit Health(int hitpoints) : hitpoints(hitpoints), total_hitpoints(hitpoints)
    {

    }
};

// Items the character has collected but not currently equipped.
struct Backpack
{
    // The items stored in the character's backpack.
    std::vector<Item *> items;

    void add_item(auto item) // Type Item *
    {
    	
    	items.push_back(item); // & ?
    }
};

// The character controlled by the player.
struct Character
{
    std::string name;
    // Character has 100 hitpoints.
    Health health{100};

    Backpack backpack;
    // Currently wielded weapon.
    Weapon *weapon{};
    // Currently worn armor.
    Armor *armor{};

    void equip(Armor* item)
    {
    	// DEFINE
    	// std::string item_str(typeid(item).name());
    	// std::cout << "item: " << item_str << std::endl;

    	// if ( item_str.find("Weapon") != std::string::npos )
    	// {
    	// 	std::cout << "Equipping weapon\n";
    	// 	weapon = item;
    	// }
    	// else if ( item_str.find("Armor") != std::string::npos )
    	// {
    	// std::cout << "Equipping armor\n";
        if (armor != nullptr)
        {
            backpack.add_item(armor);
        }

    	armor = item;

    	// }
    }

    void equip(Weapon* item)
    {
    	// std::cout << "Equipping weapon\n";
        if (weapon != nullptr)
        {
            backpack.add_item(weapon);
        }

    	weapon = item;
    }
};

// An enemy that is part of an encounter.
struct Enemy
{
    std::string name;
    Health health;
    // Damage dealt on attack.
    int damage;

    Enemy(const std::string &name, int hitpoints, int damage) 
    	: name(name), health(hitpoints), damage(damage)
	{

	}
};

// An encounter in a series and some loot which the player receives upon completion.
struct Encounter
{
    // Enemy of the encounter.
    Enemy enemy;
    // Possible loot dropped when killing the enemy.
    Item *loot;

    Encounter(const Enemy &enemy, Item *loot) : enemy(enemy), loot(loot)
    {

    }
};

#endif
