#pragma once
#include <string>
using namespace std;

class Monster {
protected:
    string mName;    // 몬스터 이름
    int mHealth;     // 몬스터 체력
    int mAttack;     // 몬스터 공격력
    string mAsciiArt; // ASCII 아트 문자열

public:
    Monster(int level, const string& type, const string& asciiArt);

    string GetName() const;
    int GetHealth() const;
    int GetAttack() const;
    void TakeDamage(int damage);
    string GetAsciiArt() const; // ASCII 아트 반환
    virtual ~Monster() {}
};
