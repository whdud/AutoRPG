#pragma once
#include <string>
using namespace std;

class Character {

public:
    Character();
	void LevelUp();
    // 이름 게터와 세터  
    string getName() const { return mName; }
    void setName(const string& name) { mName = name; }

    // 레벨 게터와 세터
    int getLevel() const { return mLevel; }
    void setLevel(int level) { mLevel = level; }

    // 최대최력 게터와 세터
    int getMaxHp() const { return mMaxHp; }
    void setMaxHp(int maxHp) { mMaxHp = maxHp; }

    // 체력 게터와 세터
    int getHp() const { return mHp; }
    void setHp(int hp) { mHp = hp; }

    // 공격력 게터와 세터
    int getAttack() const { return mAttack; }
    void setAttack(int attack) { mAttack = attack; }

    // 경험치 게터와 세터
    int getExperience() const { return mExperience; }
    void setExperience(int experience) { mExperience = experience; }

    // 골드 게터와 세터
    int getGold() const { return mGold; }
    void setGold(int gold) { mGold = gold; }

	void displayStatus();// 스테이터스 출력
	void resetCharacter();// 캐릭터 초기화(죽었을 떄)

private:
    string  mName;
    int     mLevel;
    int     mMaxHp;
    int     mHp;
    int     mAttack;
    int     mExperience;
    int     mGold;
};