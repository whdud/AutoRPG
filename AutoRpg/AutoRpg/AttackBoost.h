#pragma once

#ifndef ATTACKBOOST_H

#include "Item.h"
#include "Character.h"

class AttackBoost : public Item 
{

private:
	int mAttackIncrease;

public:

	// constructor
	AttackBoost(int price, int attackincrease);

	// character increase attack damage
	void Use(Character& charcter) override;

};

#endif
