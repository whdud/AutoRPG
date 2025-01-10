#pragma once
//����� �ּ����� ��Ŭ��尡 ���ٳ׿�?
#include <string>
using namespace std;

class Character {

public:
    Character();
    ~Character();

private:
    //��������� _����ϴ°� ���ƺ�����
    //������ �̴ϼȶ����� �� �ʱ�ȭ ����
    string  _name;
    int     _level;
    int     _maxHp;
    int     _hp;
    int     _attack;
    int     _experience;
    int     _gold;
};