#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Item.h"

using namespace std;

class Character;

class Inventory {

//인벤토리 생성자 필요!!! 
private:
    vector<shared_ptr<Item>> mItems;

public:
    void AddItem(shared_ptr<Item> item);
    void UseItem(int index, Character& character);
    void DisplayInventory() const;
    void ClearInventory();
    bool IsHealthPotion() const;
    bool IsAttackBoost() const;
};
