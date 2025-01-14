#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Item.h"

using namespace std;

class Character;

class Inventory {
private:
    vector<shared_ptr<Item>> mItems;

public:
    void AddItem(shared_ptr<Item> item);
    void UseItem(int index, Character& character);
    void DisplayInventory() const;
    void ClearInventory();
};
