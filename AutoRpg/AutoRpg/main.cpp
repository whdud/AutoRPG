#include <iostream>
#include <string>
#include <vector>
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
using namespace std;


int main(void)
{
	//����Ʈ������ �̿�?
	Character* player = new Character();
	
	//���� ����
	GameManger::GetInstance()->GenerateMonster(10);
	
	//�÷��̾� �־ ������� ����
	GameManger::GetInstance()->Battle(player);

	//�÷��̾��� �κ��丮 ���� �ڵ�
	GameManger::GetInstance()->DisplayInventory(player);
	return 0;
}
