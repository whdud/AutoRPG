﻿#include "Monster.h"
#include "defines.h"
#include <iostream>

using namespace std;

Monster::Monster(int level)
{
    mMonsterHp = rand() % (level * 10) + (level * 20); // 체력 설정
    mAttack = rand() % (level * 5) + (level * 5);   // 공격력 설정
}

string Monster::GetName() const { return mName; }
int Monster::GetMonsterHp() const { return mMonsterHp; }
int Monster::GetAttack() const { return mAttack; }


void Monster::SetBossMonster()
{
    mMonsterHp *= 1.5f;
    mAttack *= 1.5f;
    mName = "Boss";
}

void Monster::TakeDamage(int damage) { mMonsterHp = mMonsterHp - damage < 0 ? 0 : mMonsterHp - damage; }

