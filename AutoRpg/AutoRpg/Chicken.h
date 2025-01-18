#pragma once
#include "Monster.h"

class Chicken : public Monster
{
public:
 
private:
    string mAsciiArt[3]; // ASCII ��Ʈ ���ڿ�
public:
    explicit Chicken(int level);

    virtual string GetAsciiArt() override; // ASCII 아트 반환
    virtual string GetAsciiArtDeath() override;
};

