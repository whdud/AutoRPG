#include "Inventory.h"
#include "Character.h"
#include <iostream>
using namespace std;

void Inventory::addItem(shared_ptr<Item> item) {
    mItems.push_back(item);
}

void Inventory::useItem(int index, Character& character) {
    if (index >= 0 && index < mItems.size()) {
        mItems[index]->use(&character);
        mItems.erase(mItems.begin() + index);
    }
}

void Inventory::displayInventory() const {
    cout << "인벤토리:\n";
    for (size_t i = 0; i < mItems.size(); ++i) {
        cout << i + 1 << ". " << mItems[i]->GetName() << "\n";
    }
}
