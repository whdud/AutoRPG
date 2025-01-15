#pragma once
#include "Monster.h"

class Buckpip : public Monster {
public:
    explicit Buckpip(int level);
public:
    virtual string Monster::GetAsciiArt() const override { return mAsciiArt; }
private:
    string mAsciiArt; // ASCII ��Ʈ ���ڿ�
};