#pragma once
#include <string>
#include <memory>
#include <random>
#include <vector>
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

    vector<int> mShakeStrArr;
    
    int FrameIdx = 0;
public:
    explicit Monster(int level);

    string GetName() const;
    int GetMonsterHp() const;
    int GetAttack() const;

    void SetBossMonster();

    void TakeDamage(int damage);
    virtual string GetAsciiArt()  =0; // ASCII 아트 반환
    virtual string GetAsciiArtDeath() = 0;

    virtual ~Monster() {}

};
