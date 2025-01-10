#include <iostream>
#include <string>
#include <vector>
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
using namespace std;

//����� �߹� ����
int main(void)
{
	//����Ʈ������ �̿�?
	Character* player = new Character();

	GameManger::GetInstance()->SetPlayer(player);

	//���� ����
	GameManger::GetInstance()->GenerateMonster(10);
	
	//�÷��̾� �־ ������� ����
	GameManger::GetInstance()->Battle(player);

	//�÷��̾��� �κ��丮 ���� �ڵ�아느읜ㅇ
	GameManger::GetInstance()->DisplayInventory(player);
	return 0;
}
 