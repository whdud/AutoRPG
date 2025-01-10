#pragma once
//헤더엔 최소한의 인클루드가 좋다네요?
#include <string>
using namespace std;

class Character {

public:
    Character();
    ~Character();

private:
    //멤버변수엔 _사용하는게 좋아보여용
    //생성자 이니셜라이즈 로 초기화 ㄱㄱ
    string  mName;
    int     mLevel;
    int     mMaxHp;
    int     mHp;
    int     mAttack;
    int     mExperience;
    int     mGold;
};