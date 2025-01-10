#pragma once
//����� �ּ����� ��Ŭ��尡 ���ٳ׿�?
#include <string>
using namespace std;

class Character {

public:
    Character();
    ~Character();

private:
    //안녕하세요
    
    string  mName;
    int     mLevel;
    int     mMaxHp;
    int     mHp;
    int     mAttack;
    int     mExperience;
    int     mGold;
};