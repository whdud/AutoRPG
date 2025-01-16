#pragma once
#include "Monster.h"

class Buckpip : public Monster {
public:
    explicit Buckpip(int level);
public:
    virtual string GetAsciiArt()override { return mAsciiArt; }
private:
    string mAsciiArt; // ASCII ��Ʈ ���ڿ�
};