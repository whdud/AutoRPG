#include "Inventory.h"
#include "Character.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

void Inventory::AddItem(shared_ptr<Item> item) {
    mItems.push_back(item);
} 

void Inventory::UseItem(int index, Character& character) {
    if (index >= 0 && index < mItems.size()) {
        mItems[index]->Use(character);
        mItems.erase(mItems.begin() + index);
    }
    else {
        cout << "잘못된 아이템 인덱스입니다.\n";
    }
}

void Inventory::RemoveItem(int index) {

    mItems.erase(mItems.begin() + index);

}

void Inventory::DisplayInventory() const {
    cout << "인벤토리:\n";
    for (size_t i = 0; i < mItems.size(); ++i) {
        cout << i + 1 << ". " << mItems[i]->GetName() << " (가격: " << mItems[i]->GetPrice() * 0.6<< ")\n";
    }
    if (mItems.empty()) {
        cout << "(비어 있음)\n";
    }
}

void Inventory::ClearInventory() {
    mItems.clear();
}
bool Inventory::IsHealthPotion() const {
    for (const auto& item : mItems) {
        if (dynamic_cast<HealthPotion*>(item.get())) { // HealthPotion인지 확인
            return true;
        }
    }
    return false;
}

bool Inventory::IsAttackBoost() const {
    for (const auto& item : mItems) {
        if (dynamic_cast<AttackBoost*>(item.get())) { // AttackBoost인지 확인
            return true;
        }
    }
    return false;
}

const vector<shared_ptr<Item>>& Inventory::GetItems() const {

    return mItems;

}
