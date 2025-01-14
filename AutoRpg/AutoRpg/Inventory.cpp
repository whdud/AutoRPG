#include "Inventory.h"
#include "Character.h"

void Inventory::AddItem(shared_ptr<Item> item) {
    mItems.push_back(item);
}

void Inventory::UseItem(int index, Character& character) {
    if (index >= 0 && index < mItems.size()) {
        mItems[index]->use(character);
        mItems.erase(mItems.begin() + index);
    }
    else {
        cout << "잘못된 아이템 인덱스입니다.\n";
    }
}

void Inventory::DisplayInventory() const {
    cout << "인벤토리:\n";
    for (size_t i = 0; i < mItems.size(); ++i) {
        cout << i + 1 << ". " << mItems[i]->GetName() << " (가격: " << mItems[i]->GetPrice() << ")\n";
    }
    if (mItems.empty()) {
        cout << "(비어 있음)\n";
    }
}

void Inventory::ClearInventory() {
    mItems.clear();
}
