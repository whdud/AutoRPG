#pragma once

#ifndef HEALTHPOTION_T

#include "Item.h" 
#include "Character.h"

class HealthPotion : public Item
{

private:
	int mHealthRestore;

public:

	// constructor
	HealthPotion(int price, int healthrestore);

	// Character hp restore
	virtual void Use(TSharedRef<Character>  character) override;

};

#endif