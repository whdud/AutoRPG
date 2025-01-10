#pragma once
/*
������� ������ �ּ�ȭ �ϱ� ���� ���漱�� �߽��ϴ�.
*/
#include <vector>
class Monster;
class Character;


class GameManger
{
public:
	static GameManger* GetInstance()//&->*������ �������� �ٲ���ϴ�.
	{
		static GameManger gm;
		return &gm;//->�ּ� ��ȯ 
	}

public:
	void SetPlayer(Character* player);

	//�Ŵ������� ����� ����-> �Ŵ������� ��������
	Monster*/*�ּҹ�ȯ*/ GenerateMonster(int level);

	//��Ʋ����
	void Battle(Character* player);

	//�κ��丮display
	void DisplayInventory(Character* player);

public:
	GameManger();
	~GameManger();

private:
	//�÷��̾� ����
	Character* mMyCharPtr;
	//���� ���ͷ� ����?
	std::vector<int> mMonsterVec;
	
};



