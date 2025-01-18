#include "Item.h"

Item::Item(const string& Itemname, int price) : mItemName(Itemname), mPrice(price) {}

string Item::GetName() const
{

	return mItemName;

}

int Item::GetPrice() const
{

	return mPrice;

}