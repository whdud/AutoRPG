#pragma once
#include "Monster.h"
#include <string>
class Plumpkin : public Monster {
public:
    explicit Plumpkin(int level);
public:
    virtual string GetAsciiArt()  override;
    virtual string GetAsciiArtDeath()  override;
private:
  
    string mAsciiArt[3]; // ASCII ��Ʈ ���ڿ�
};
