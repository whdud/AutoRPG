#pragma once
#include <iostream>
#include <windows.h>
//#include <atomic>
#include <chrono>
#include <conio.h> 
#include <vector>
#include <deque>
using namespace std;

class Character;
class Monster;
class Shop;
class Inventory;

enum BTTSTATE
{
	DELAY,
	READY,
	MONSTER,
	PLAYER,
	DIE,
	WIN,
	SHOP,
	STATUS,
	CLOSE,
};
enum CLOSESTATE
{
	cRESULT,
	cDIE,
	cWIN,
	cBOSS_WIN,
	cDELAY
};
enum BTTRESULT
{
	rEXIT = -1,
	rEMPTY = 0,
	rFAIL,
	rWIN
};
struct sShake
{
	string shakeStr = "";
	float  shakeTime = 1.f;
	void Reset()
	{
		shakeStr = "";
		shakeTime = 1.f;
	}
};
class BattleManager
{
public:
	BattleManager();
	BattleManager(Character* player);
	~BattleManager();

public:
	BTTRESULT Update();
	void ReadyBattle(Monster* monster);

	//게임중에 아이템 먹기.
	void UseItem(int item);

	void Timer();
	float GetDeltaTime();

private:
	void SetState(BTTSTATE st);
	void Ready();
	void PlayerTurn();
	void MonsterTurn();
	void PlayerWin();
	void PlayerDie();
	void SHOP();
	void Status();
	void Close();

	void SetSubState(int st);
	void NextGameTurn();
	void OutputMsg(  string str = "" , bool isNewPage = false);
	void InputMsg(string str );

	int RandRange(int min , int max);
	void CleanScreen();
	int DropItem();
	void KeyButton();
	
public:
	LARGE_INTEGER frequency ;
	LARGE_INTEGER cur  ;
	LARGE_INTEGER prevFrame;
	float deltaTime = 0.f;
	float fps = 0.f, fpsTime = 0.f;
	float mTime = 0.f;
	float mBattleTime = 0.f;
	int fpsCounter = 0;

private:
	BTTSTATE mGameState = BTTSTATE::DELAY;
	BTTSTATE mPrvGameState = BTTSTATE::DELAY;
	BTTRESULT mEBTTReult = BTTRESULT::rEMPTY;
	int mSubState = 0;

	deque<string> mStrArr;

	Character*  mPlayer;
	Monster*	mMonster;
	Shop*		mShop;

	int mMonsterHp = 10;
	sShake shake;
};


