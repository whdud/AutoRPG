#pragma once
#include <string>
using namespace std;

class Character {

public:
    Character();
	void LevelUp();
protected:
    void displayStatus();
	void resetCharacter();

private:
    string  mName;
    int     mLevel;
    int     mMaxHp;
    int     mHp;
    int     mAttack;
    int     mExperience;
    int     mGold;
};