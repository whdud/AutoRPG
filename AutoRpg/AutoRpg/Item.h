#pragma once

#ifndef ITEM_H

#include <string>

using namespace std;

// forward declaration
class Character;

class Item
{

protected:

	string mItemName;
	int mPrice;

public:

	//	Item Constructor
	Item(const string& Itemname, int price);

	//  Item Destructor
	virtual ~Item() = default;

	//	pure virtual function
	virtual void Use(TSharedRef<Character> character) = 0;

	//	Item Name
	string GetName() const;

	// Item price
	int GetPrice() const;

};



#endif
