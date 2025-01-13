#pragma once

#ifndef SHOP_H

#include <vector>
#include "Item.h"
#include "Character.h"
#include <memory>

using namespace std;

class Shop 
{
private:

	// item storage
	vector<shared_ptr<Item>> mAvailableItems;

public:

	//	constructor
	Shop();

	//	Item list
	void DisplayItems() const;

	// Buy item
	void BuyItem(int index, Character& character);

};


#endif
