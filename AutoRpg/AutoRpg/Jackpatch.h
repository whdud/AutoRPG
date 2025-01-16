#pragma once
#include "Monster.h"

class Jackpatch : public Monster {
public:
    explicit Jackpatch(int level);

public:
    virtual string GetAsciiArt() override;

private:
    string mAsciiArt; // ASCII ��Ʈ ���ڿ�

};