#pragma once
#include "Monster.h"

class Buckpip : public Monster {
public:
    Buckpip(int level);
public:
    virtual string Monster::GetAsciiArt() const override { return mAsciiArt; }
private:
    string mAsciiArt; // ASCII 아트 문자열
};