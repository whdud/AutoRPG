#pragma once
#include <string>
#include <memory>
#include <random>
#include "Character.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Inventory.h"

using namespace std;

class Monster {

protected:
    string mName;    // 몬스터 이름
    int mMonsterHp;     // 몬스터 체력
    int mAttack;     // 몬스터 공격력

public:
    Monster(int level);

    string GetName() const;
    int GetMonsterHp() const;
    int GetAttack() const;
    void TakeDamage(int damage);
    virtual string GetAsciiArt() const =0; // ASCII 아트 반환
    virtual ~Monster() {}

    void DropItem(Character& character); // Drop Item

};
