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
    void addItem(shared_ptr<Item> item);
    void useItem(int index, Character& character);
    void displayInventory() const;
    void clearInventory();
};
