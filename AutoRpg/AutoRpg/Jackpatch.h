#pragma once
#include "Monster.h"

class Jackpatch : public Monster {
public:
    explicit Jackpatch(int level);

public:
    virtual string Monster::GetAsciiArt() const override{ return mAsciiArt; }

private:
    string mAsciiArt; // ASCII 아트 문자열

};