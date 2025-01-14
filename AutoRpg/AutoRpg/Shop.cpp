#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

using namespace std;

Shop::Shop() 
{

	mAvailableItems.push_back(make_shared<HealthPotion>(10, 50));
	mAvailableItems.push_back(make_shared<AttackBoost>(20, 10));

}

void Shop::DisplayItems() const
{

	cout << "You're arrived the shop, which one do you want?" << endl;

	for (size_t i = 0; i < mAvailableItems.size(); i++) 
	{

		cout << i + 1 << ". " << mAvailableItems[i]->GetName() << " [" << mAvailableItems[i]->GetPrice() << " Gold]" << endl;

	}

}

void Shop::BuyItem(int index, Character& character)
{

	shared_ptr<Item>& selectedItem = mAvailableItems[index];

	if (character.GetGold() < selectedItem->GetPrice()) {

		cout << "not enough Gold" << endl;
		return;

	}
	character.ReduceGold(selectedItem->GetPrice());
	character.AddItem(selectedItem);

	cout << "Item purchased successfully" << endl;

}