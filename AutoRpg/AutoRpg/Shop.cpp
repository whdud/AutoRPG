#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

using namespace std;

Shop::Shop() 
{

	mAvailableItems.push_back(make_shared<HealthPotion>(10, 10));
	mAvailableItems.push_back(make_shared<AttackBoost>(20, 3));

}

void Shop::DisplayItems() const
{

	cout << "Buy items" << endl;

	for (size_t i = 0; i < mAvailableItems.size(); i++) 
	{

		cout << i + 1 << ". " << mAvailableItems[i]->GetName() << " [" << mAvailableItems[i]->GetPrice() << " Gold]" << endl;

	}

}

void Shop::BuyItem(int index, Character& character)
{
	if (index < 0 || index >= static_cast<int>(mAvailableItems.size()))
	{
		cout << "Invalid Item" << endl;
		return;
	}
	shared_ptr<Item> selectedItem = mAvailableItems[index];

	if (character.GetGold() < selectedItem->GetPrice()) {

		cout << "not enough Gold" << endl;
		return;

	}
	character.ReduceGold(selectedItem->GetPrice());
	character.AddItem(selectedItem);

	cout << "Item purchased successfully" << endl;
	cout << "Press Q" << endl;
}

void Shop::SellItems(int index, Character& character) {

	if (index < 0 || index >= static_cast<int>(mAvailableItems.size())) 
	{
		cout << "Invalid item" << endl;
		return;
	}

	Inventory& inventory = character.GetInventory();
	const auto& items = inventory.GetItems();

	shared_ptr<Item> itemsell = items[index];
	int SellPrice = itemsell->GetPrice() * 0.6;

	character.AddGold(SellPrice);
	inventory.RemoveItem(index);
	
	cout << "Sold " << itemsell->GetName() << " for " << SellPrice << " Gold" << endl;
	cout << "Press Q" << endl;
}
