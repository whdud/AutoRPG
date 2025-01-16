#pragma once
#include <string>
#include <memory>
#include "Inventory.h"
#include "Item.h"

using namespace std;

/*std::enable_shared_from_this*/
class Character 
    : public std::enable_shared_from_this<Character>
{
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
    explicit Character(const string& charName);

    string GetName() const;
    void SetName(const string& name);

    int GetLevel() const;
    void SetLevel(int level);
    void SetAttack(int attack);
    bool LevelUp();
    void AddItem(shared_ptr<Item> item);
    void UseItem(int index);
    void DisplayStatus() const;
    void ResetCharacter();

    void IncreaseHealth(int amount);
    void IncreaseAttack(int amount);
    int GetGold() const;
    void ReduceGold(int amount);
    void AddGold(int amount);
    int GetAttack() const;
    int GetHp() const;
    void SetHp(int hp);
    void SetGold(int gold);
    int GetMaxHp() const;
    bool SetExperience(int exp);
    bool IsHealthPotion() const;
    bool IsAttackBoost() const;

    TSharedRef<Inventory> GetInventory();

};
