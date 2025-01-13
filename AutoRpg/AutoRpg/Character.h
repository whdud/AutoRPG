#pragma once

#ifndef CHARACTER_H

#include <string>

using namespace std;

class Character 
{

private:
	string name;
	int health;
	int maxhealth;
	int attack;
	int gold;

public:

	Character(const string& name, int health, int attack, int gold);
	void displaystatus() const;
	void addGold(int amount);
	void reduceGold(int amount);
	void increaseHealth(int amount);
	void increaseAttack(int amount);
	int GetGold() const;

};



#endif