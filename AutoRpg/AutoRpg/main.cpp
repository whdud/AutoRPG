#include <iostream>
#include <string>
#include <vector>
#include "defines.h"
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "BattleManager.h"
#include "SoundMgr.h"
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
	//system("mode con: cols=500 lines=1280");
	system("color 0A");
	//스마트포인터 이용?
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);
	

	std::string playerName;
	while (true) {
		cout << "이름을 입력하세요....\n";
		std::getline(std::cin, playerName);

		// UTF-8에서 공백 확인
		if (std::any_of(playerName.begin(), playerName.end(), [](unsigned char c) {
			return std::isspace(c);
			})) {
			cout << "공백이 존재합니다. 다시 입력하세요..\n";
			continue;
		}
		else {
			break;
		}
	}
	//while (true)
	//{
	//	cout << "이름을 입력하세요....\n";
	//	std::getline(std::cin, playerName); // 공백 포함한 문자열 입력받기
	//	if (std::any_of(playerName.begin(), playerName.end(), isspace))
	//	{
	//		cout << "공백이 존재합니다. 다시입력하세요..\n";
	//		continue;
	//	}
	//	else
	//		break;
	//}
	Character* player = new Character(playerName);

	GameManager::GetInstance()->SetPlayer(player);
	
	BattleManager* bttMgr = new BattleManager(player);

	GET_SINGLE(SoundMgr)->PlayBGM(0);
	int GameLevel = 1;
	int GameResult = 0;
	while (true)
	{
		bttMgr->ReadyBattle(GET_SINGLE(GameManager)->GenerateMonster(GameLevel));

		while (BTTRESULT::rEMPTY == GameResult) {
			GameResult = bttMgr->Update();
		}

		if (BTTRESULT::rEXIT == GameResult)
			exit(0);

		GameLevel = BTTRESULT::rWIN == GameResult ? GameLevel + 1 : GameLevel;
		GameResult = BTTRESULT::rEMPTY;



		//만든 몬스터와 바로 배틀 ㄱㄱ 안에서 이겼으면 상점스킵 or 상점방문  
		
		//상점 가는 코드

		//도전과제 10레벨 찍고 보스몬스터 나옴-> 클리어하면  while문 탈출
	}
	

	return 0;
}

