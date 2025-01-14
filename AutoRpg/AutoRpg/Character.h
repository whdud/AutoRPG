#pragma once
#include <string>
#include <memory>
#include "Inventory.h"
#include "Item.h"

using namespace std;

class Character {
private:
    string mName; // 캐릭터 이름
    int mLevel;   // 캐릭터 레벨
    int mMaxHp;   // 최대 체력
    int mHp;      // 현재 체력
    int mAttack;  // 공격력
    int mExperience; // 경험치
    int mGold;    // 골드
    Inventory mInventory; // 인벤토리 객체

public:
    Character(const string& charName);

    string getName() const;
    void setName(const string& name);

    int getLevel() const;
    void setLevel(int level);

    void levelUp();
    void addItem(shared_ptr<Item> item);
    void useItem(int index);
    void displayStatus() const;
    void resetCharacter();
};
