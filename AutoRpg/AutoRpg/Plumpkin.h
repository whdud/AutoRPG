#pragma once
#include "Monster.h"

class Plumpkin : public Monster {
public:
    Plumpkin(int level);
public:
    virtual string Monster::GetAsciiArt() const override { return mAsciiArt; }
private:
    string mAsciiArt; // ASCII 아트 문자열
};
