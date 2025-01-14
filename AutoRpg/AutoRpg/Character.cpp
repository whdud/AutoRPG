#include "Character.h"
#include <iostream>
using namespace std;

Character::Character(const string& charName)
    : mName(charName), mLevel(1), mMaxHp(100), mHp(100), mAttack(10), mExperience(0), mGold(0) {
}

string Character::GetName() const { return mName; }
void Character::SetName(const string& name) { mName = name; }

int Character::GetLevel() const { return mLevel; }
void Character::SetLevel(int level) { mLevel = level; }

void Character::LevelUp() {
    if (mExperience >= 100 && mLevel < 10) {
        mExperience -= 100;
        mLevel++;
        mMaxHp += mLevel * 20;
        mHp = mMaxHp;
        mAttack += mLevel * 5;
        cout << "레벨업! 현재 레벨: " << mLevel << "\n";
    }
}

void Character::IncreaseHealth(int amount) {

    mHp = min(mHp + amount, mMaxHp);
    cout << "Health increased " << amount << ". Current Health: " << mHp << endl;

}

void Character::IncreaseAttack(int amount) {

    mAttack += amount;
    cout << "Attack increased " << amount << ". Current AttackDamage: " << mAttack << endl;

}

void Character::ReduceGold(int amount) {

    mGold -= amount;

}

int Character::GetGold() const {

    return mGold;

}

void Character::AddItem(shared_ptr<Item> item) {
    mInventory.AddItem(item);
}

void Character::UseItem(int index) {
    mInventory.UseItem(index, *this);
}

void Character::DisplayStatus() const {
    cout << "--- " << mName << " 상태 ---\n";
    cout << "레벨: " << mLevel << "\n";
    cout << "체력: " << mHp << "/" << mMaxHp << "\n";
    cout << "공격력: " << mAttack << "\n";
    cout << "골드: " << mGold << "\n";
    cout << "경험치: " << mExperience << "\n";
    mInventory.DisplayInventory();
    cout << "-------------------------\n";
}

void Character::ResetCharacter() {
    mLevel = 1;
    mMaxHp = 100;
    mHp = mMaxHp;
    mAttack = 10;
    mExperience = 0;
    mGold = 0;
    mInventory.ClearInventory();
    cout << "캐릭터가 초기화되었습니다.\n";
}
