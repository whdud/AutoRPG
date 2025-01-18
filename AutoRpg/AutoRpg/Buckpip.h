#pragma once
#include "Monster.h"

class Buckpip : public Monster {
public:
    explicit Buckpip(int level);
public:
    virtual string GetAsciiArt()override;
    virtual string GetAsciiArtDeath()  override;
private:
    string mAsciiArt[3]; // ASCII ��Ʈ ���ڿ�
};