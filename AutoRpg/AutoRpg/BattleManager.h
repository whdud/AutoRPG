#pragma once
#include <iostream>
#include <windows.h>
//#include <atomic>
#include <chrono>
#include <conio.h> 
#include <vector>

using namespace std;

class Character;
class Monster;
class Shop;
class Inventory;

enum BTTSTATE
{
	EMPTY,
	READY,
	MONSTER,
	PLAYER,
	WIN,
	DIE,
	STORE,
	STATUS,
	CLOSE,
};
enum CLOSESTATE
{
	cRESULT,
	cDIE,
	cWIN,
	cDELAY
};
enum BTTRESULT
{
	rEMPTY,
	rFAIL,
	rWIN
};
class BattleManager
{
public:
	BattleManager();
	~BattleManager();
public:
	BTTRESULT Update(Character* player);
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
	void Store();
	void Status();
	void Close();

	void SetSubState(int st);
	void NextGameTurn();
	void OutputMsg(  string str = "" , bool isNewPage = false);
	void InputMsg(string str );

	int RandRange(int min , int max);
	void CleanScreen();
	int DropItem();
	
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
	BTTSTATE mGameState = BTTSTATE::EMPTY;
	BTTSTATE mPrvGameState = BTTSTATE::EMPTY;
	BTTRESULT mEBTTReult = BTTRESULT::rEMPTY;
	int mSubState = 0;

	vector<string> mStrArr;

	Character*  mPlayer;
	Monster*	mMonster;
	Shop*		mShop;
	Inventory*	mInventory;

	int mMonsterHp = 10;

};

