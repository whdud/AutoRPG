#pragma once
/*
������� ������ �ּ�ȭ �ϱ� ���� ���漱�� �߽��ϴ�.
*/
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
	Character* myChar;
	//���� ���ͷ� ����?

};



