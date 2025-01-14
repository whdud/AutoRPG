#include "Character.h"
#include <iostream>
using namespace std;

Character::Character(const string& charName)
    : mName(charName), mLevel(1), mMaxHp(100), mHp(100), mAttack(10), mExperience(0), mGold(0) {
}

string Character::getName() const { return mName; }
void Character::setName(const string& name) { mName = name; }

int Character::getLevel() const { return mLevel; }
void Character::setLevel(int level) { mLevel = level; }

void Character::levelUp() {
    if (mExperience >= 100 && mLevel < 10) {
        mExperience -= 100;
        mLevel++;
        mMaxHp += mLevel * 20;
        mHp = mMaxHp;
        mAttack += mLevel * 5;
        cout << "레벨업! 현재 레벨: " << mLevel << "\n";
    }
}

void Character::addItem(shared_ptr<Item> item) {
    mInventory.addItem(item);
}

void Character::useItem(int index) {
    mInventory.useItem(index, *this);
}

void Character::displayStatus() const {
    cout << "--- " << mName << " 상태 ---\n";
    cout << "레벨: " << mLevel << "\n";
    cout << "체력: " << mHp << "/" << mMaxHp << "\n";
    cout << "공격력: " << mAttack << "\n";
    cout << "골드: " << mGold << "\n";
    cout << "경험치: " << mExperience << "\n";
    mInventory.displayInventory();
    cout << "-------------------------\n";
}

void Character::resetCharacter() {
    mLevel = 1;
    mMaxHp = 100;
    mHp = mMaxHp;
    mAttack = 10;
    mExperience = 0;
    mGold = 0;
    mInventory.clearInventory();
    cout << "캐릭터가 초기화되었습니다.\n";
}
