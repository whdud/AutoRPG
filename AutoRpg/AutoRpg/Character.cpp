#include <iostream>
#include "Character.h"

using namespace std;

Character::Character()
			:mName("Player"),
			 mLevel(1),
			 mMaxHp(10),
			 mHp(mMaxHp),
			 mAttack(2),
			 mExperience(0),
			 mGold(0)
{
	/*mName = "Player";
	mLevel = 1;
	mMaxHp = 10;
	mHp = mMaxHp;
	mAttack = 2;
	mExperience = 0;
	mGold = 0;*/
}

void Character::displayStatus()
{
    cout << "\n--- " << mName << "'s Status ---\n";
    cout << "Level: " << mLevel << "\nHP: " << mHp << "/" 
		<< mMaxHp << "\nAttack: " << mAttack << "\nGold: "
		<< mGold << "\nExperience: " << mExperience << "\n";
}

void Character::LevelUp()//레벨업 함수
{
    if (mLevel < 10) 
    {
        mLevel++; // 레벨 증가
        mMaxHp += mLevel * 20; // 레벨에 따라 최대 체력 증가
        mHp = mMaxHp; // 최대 체력으로 회복
        mAttack += mLevel * 5; // 공격력 증가
        cout << "레벨업! " << mLevel << "\n";
    }
    else
    {
        cout << "만렙입니다!!\n";
    }
}

void Character::resetCharacter()//캐릭터 초기화(죽었을 떄)
{
	mName = "Player";
	mLevel = 1;
	mMaxHp = 10;
	mHp = mMaxHp;
	mAttack = 2;
	mExperience = 0;
	mGold = 0;
}