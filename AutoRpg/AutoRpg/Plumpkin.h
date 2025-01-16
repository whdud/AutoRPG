#pragma once
#include "Monster.h"

class Plumpkin : public Monster {
public:
    explicit Plumpkin(int level);
public:
    virtual string Monster::GetAsciiArt()  override;
  
 
private:
    int FrameIdx = 0;
    string mAsciiArt[3]; // ASCII ��Ʈ ���ڿ�
};
