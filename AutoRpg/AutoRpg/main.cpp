#include <iostream>
#include <string>
#include <vector>
#include "defines.h"
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "BattleManager.h"
using namespace std;

//영환이꺼 확인~
//int main() {
//    // 캐릭터 생성
//    Character player("Hero");
//    cout << "게임 시작! 캐릭터 생성 완료.\n";
//    player.DisplayStatus();
//	return 0;
//}
   
//깃허브 야발 ㅎㅇ
int main(void)
{
	system("color 0A");
	//스마트포인터 이용?
	

	std::string playerName;
	while (true)
	{

		cout << "이름을 입력하세요....\n";
		std::getline(std::cin, playerName); // 공백 포함한 문자열 입력받기
		if (std::any_of(playerName.begin(), playerName.end(), isspace))
		{
			cout << "공백이 존재합니다. 다시입력하세요..\n";
			continue;
		}
		else
			break;
	}
	Character* player = new Character(playerName);

	GameManger::GetInstance()->SetPlayer(player);
	
	BattleManager* bttMgr = new BattleManager();

	GameManger::GetInstance()->SetBattleMgr(bttMgr);

	int GameLevel = 1;
	int GameResult = 0;
	while (true)
	{
		//몬스터 레벨입력후 랜덤 1마리 생성
		GET_SINGLE(GameManger)->SetMonster(GET_SINGLE(GameManger)->GenerateMonster(GameLevel));
		if (player->GetLevel() >= 10)
		{
			//몬스터얻어와서 보스로 바꿔주고 이름도 "Boss" 배틀안에서 Boss 확인됨  
			GET_SINGLE(GameManger)->GetMonster()->SetBossMonster();
			
		}
		GET_SINGLE(GameManger)->StartBattle();

		while (BTTRESULT::rEMPTY == GameResult) {
			GameResult = GET_SINGLE(GameManger)->Battle(player);
		}

		GameLevel = BTTRESULT::rWIN == GameResult ? GameLevel + 1 : GameLevel;
		GameResult = BTTRESULT::rEMPTY;

		//만든 몬스터와 바로 배틀 ㄱㄱ 안에서 이겼으면 상점스킵 or 상점방문  
		
		//상점 가는 코드

		//도전과제 10레벨 찍고 보스몬스터 나옴-> 클리어하면  while문 탈출
	}
	

	return 0;
}

