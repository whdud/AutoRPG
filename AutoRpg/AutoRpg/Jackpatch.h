#pragma once
#include "Monster.h"

class Jackpatch : public Monster {
public:
    explicit Jackpatch(int level);

public:
    virtual string GetAsciiArt() override;
    virtual string GetAsciiArtDeath()  override;
private:
    string mAsciiArt[3]; // ASCII ��Ʈ ���ڿ�

};