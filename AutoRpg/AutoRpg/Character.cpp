#include "Character.h"
#include <iostream>

Character::Character(const string& name, int health, int attack, int gold) : name(name), health(health), maxhealth(health), attack(attack), gold(gold) {}

void Character::displaystatus() const 
{

	cout << "Character: " << name << endl;
	cout << "Health: " << health << endl;
	cout << "Attack: " << attack << endl;
	cout << "Gold: " << gold << endl;

}

void Character::addGold(int amount) 
{

	gold += amount;

}

void Character::reduceGold(int amount)
{

	gold -= amount;

}

void Character::increaseHealth(int amount) 
{

	health = min(health + amount, maxhealth);
	cout << "Health increased by " << amount << ". Current health: " << health << endl;

}

void Character::increaseAttack(int amount)
{

	attack += amount;
	cout << "Attack increased by " << amount << ". current attack: " << attack << endl;

}

int Character :: GetGold() const
{

	return gold;

}