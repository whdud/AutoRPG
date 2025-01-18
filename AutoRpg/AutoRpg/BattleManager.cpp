#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Shop.h"
#include "Inventory.h"
#include "defines.h"
#include "SoundMgr.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <deque>


enum {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};
BattleManager::BattleManager(Character* player) :mPlayer(player)
{
    QueryPerformanceFrequency(&frequency); // 한번만 읽어들이면 된다.
    QueryPerformanceCounter(&prevFrame); // 이전틱 기억

    mShop = new Shop;
}

BattleManager::~BattleManager()
{
    delete mShop;
}

BTTRESULT BattleManager::Update()//Character* player
{
    //mPlayer = player;
    Timer();
    //std::cout << "\033[H";
    switch (mGameState) {
    case BTTSTATE::DELAY:
        break;
    case BTTSTATE::READY:
        Ready();
        break;
    case BTTSTATE::MONSTER:
        MonsterTurn();
        break;
    case BTTSTATE::PLAYER:
        PlayerTurn();
        break;
    case BTTSTATE::WIN:
        PlayerWin();
        break;
    case BTTSTATE::DIE:
        PlayerDie();
        break;
    case BTTSTATE::SHOP:
        SHOP();
        break;
    case BTTSTATE::STATUS:
        Status();
        break;
    case BTTSTATE::CLOSE:
        Close();
        break;
    }

    KeyButton();

    if (mGameState == BTTSTATE::DELAY || mEBTTReult == BTTRESULT::rEXIT) // Start Delay or Next Game
        return mEBTTReult;

    return BTTRESULT::rEMPTY;
}
void BattleManager::KeyButton()
{
    if (_kbhit()) {
        char input = _getch();
        if (BTTSTATE::PLAYER == mGameState)
        {
            if (input == '1')
                UseItem(ITEM::HEALTH_POTION);
            else if (input == '2')
                UseItem(ITEM::ATTACK_BOOST);
        }
        else if (BTTSTATE::CLOSE == mGameState)
        {
            if (CLOSESTATE::cDIE == mSubState)//ReStartGame:A / OutGame:Q 
            {
                if (input == 'a')//
                {
                    mPlayer->ResetCharacter();
                    SetState(BTTSTATE::DELAY);
                }
                else if (input == 'q')
                    mEBTTReult = BTTRESULT::rEXIT;
                
            }
            else// CLOSESTATE::WIN  // Store:A /Mob hunting:S / Status:D 
            {
                if (input == 'a')//
                    SetState(BTTSTATE::SHOP);
                else if (input == 's')
                {
                    SetState(BTTSTATE::DELAY);
                }
                else if (input == 'd')
                    SetState(BTTSTATE::STATUS);
            }
        }
        else if (BTTSTATE::SHOP)
        {
            if (input == 'q')//
                SetState(BTTSTATE::CLOSE);
        }
    }
}
void BattleManager::SetState(BTTSTATE st)
{
    mPrvGameState = mGameState;
    mGameState = st;
    mSubState = 0;
    mBattleTime = 0.f;

    if (BTTSTATE::WIN == mGameState)
        mEBTTReult = BTTRESULT::rWIN;
    else if (BTTSTATE::DIE  == mGameState)
        mEBTTReult = BTTRESULT::rFAIL;
    else if (BTTSTATE::READY == mGameState)
        mEBTTReult = BTTRESULT::rEMPTY;
}

void BattleManager::Ready()
{
    switch (mSubState)
    {
        case 0:
            if (mMonster == nullptr)
                return;

            mBattleTime += GetDeltaTime();
            if (1.f < mBattleTime)
            {
                CleanScreen();
                if (mMonster->GetName() == "Boss")
                {
                    GET_SINGLE(SoundMgr)->StopBGM();
                    GET_SINGLE(SoundMgr)->PlayBGM(1);
                    InputMsg("              ========================= ");
                    InputMsg("    ========== BOSS가 등장 하였습니다! ==========");
                    OutputMsg("              =========================");
                }
                else 
                {
                    InputMsg("  ");
                    InputMsg("  ");
                    InputMsg("  ");
                    OutputMsg("         ========== BATTLE START ==========");
                }
                SetSubState(mSubState+1);
            }
            break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (1.f < mBattleTime)
            {
                BTTSTATE St = BTTSTATE( RandRange(2,3) );
                SetState(St);
            }
            break;
        case 2:

            break;
    }
}

void BattleManager::Close()
{
    switch (mSubState)
    {
    case CLOSESTATE::cRESULT:
            if ( BTTRESULT::rFAIL == mEBTTReult)
            {
                InputMsg(" ");
                InputMsg(" ");
                OutputMsg("    ====  새로하기 : A / 종료하기 : Q  ====");
                SetSubState(CLOSESTATE::cDIE);
            }
            else
            {
                if (BTTSTATE::SHOP == mPrvGameState || BTTSTATE::STATUS == mPrvGameState)
                    CleanScreen();

                if ("Boss" == mMonster->GetName()) 
                {
                    InputMsg(" ");
                    InputMsg(" ");
                    InputMsg("            ======  전투 종료  ======");
                    InputMsg(" ");
                    InputMsg("     축하합니다! 이렇게 맛있는 치킨이 되셨습니다!");
                    OutputMsg("                    게임 종료");
                    SetSubState(CLOSESTATE::cBOSS_WIN);
                }
                else {
                    InputMsg(" ");
                    InputMsg(" ");
                    InputMsg("            ======  전투 종료  ======");
                    InputMsg(" ");
                    OutputMsg("  상점: A  / 몬스터 사냥: S  / 스테이터스 확인: D");
                    SetSubState(CLOSESTATE::cWIN);
                }
            }
            break;
    case CLOSESTATE::cDIE:break;//Player die / delay Select Game
    case CLOSESTATE::cWIN: break;
    case CLOSESTATE::cBOSS_WIN:
        mBattleTime += GetDeltaTime();
        if (3.f < mBattleTime)
        {
            mBattleTime = 0.f;
            mEBTTReult = BTTRESULT::rEXIT;
        }
        break;
    case CLOSESTATE::cDELAY: break;
    }
}

void BattleManager::ReadyBattle(Monster* monster )
{
    //SAFE_DELETE(mMonster);


    mMonster = monster;
    SetState(BTTSTATE::READY);
}
 
void BattleManager::UseItem(ITEM item)
{
    bool isItem = false;
    isItem = mPlayer->UseItem(item);
    string itemName = item == ITEM::HEALTH_POTION ? "Heal Postion" : "AttackBoots";
    if (isItem)
    {
        GET_SINGLE(SoundMgr)->PlayEffect(7);
        OutputMsg("        Use Item " + itemName );
    }
    else
        OutputMsg("        Empty "+ itemName );
}

void BattleManager::PlayerTurn()
{
    switch (mSubState)
    {
        case 0:
        {
            int randAttack = mPlayer->GetAttack()+ RandRange(0, 5) ;
           
            if (randAttack == 0)
            {
                GET_SINGLE(SoundMgr)->PlayEffect(16);
                OutputMsg("       플레이어 공격!, 몬스터 방어 성공!");
            }
            else
            {
                int randIdx = RandRange(2, 3);
                if (mMonster->GetName() == "Plumpkin")//hobak
                    randIdx = RandRange(2, 3);
                else if (mMonster->GetName() == "Jackpatch") // tirano
                    randIdx = RandRange(2, 3);
                else//Buckpip kkokko
                    randIdx = RandRange(9, 10);
                GET_SINGLE(SoundMgr)->PlayEffect(randIdx);

                mMonster->TakeDamage(randAttack);
                OutputMsg("       플레이어 공격!, 몬스터 " + to_string(randAttack) + "의 데미지를 입다.");
            }
            shake.shakeTime = 0.5f;
            SetSubState(mSubState + 1);
        }break;
        case 1:
            mBattleTime += GetDeltaTime();
            shake.shakeTime -= GetDeltaTime();
            if (0.07f < mBattleTime)
            {
                OutputMsg();
                SetSubState(mSubState + 1);
            }
            break;
        case 2:
            mBattleTime += GetDeltaTime();
            shake.shakeTime -= GetDeltaTime();
            if (0.07f < mBattleTime)
            {
                if (0.f >= shake.shakeTime)
                {
                    shake.Reset();
                    OutputMsg();
                    SetSubState(mSubState + 1);
                }
                else {
                    OutputMsg();
                    SetSubState(mSubState - 1);
                }
            }
            break;
        case 3:
            if (0 == mMonster->GetMonsterHp())
            {
                int sIdx = 0;
                if (mMonster->GetName() == "Plumpkin")//hobak
                    sIdx = RandRange(12, 15);
                else if (mMonster->GetName() == "Jackpatch") // tirano
                    sIdx = RandRange(12, 15);
                else if (mMonster->GetName() == "Buckpip")//Buckpip kkokko
                    sIdx = 11;
                else if (mMonster->GetName() == "Boss")
                    sIdx = 11;//RandRange(12, 15);

                GET_SINGLE(SoundMgr)->PlayEffect(sIdx);
                OutputMsg();
                SetState(BTTSTATE::WIN);
            }
			else
                 SetSubState(mSubState + 1);
            break;
        case 4:
            mBattleTime += GetDeltaTime();
            if (1.f < mBattleTime)
                NextGameTurn();
            break;
    }
}

void BattleManager::MonsterTurn()
{
    switch (mSubState)
    {
        case 0:
        {
            int randAttack =  RandRange(0, 5);
            if (randAttack == 0)
            {
                GET_SINGLE(SoundMgr)->PlayEffect(16);
                OutputMsg("       몬스터 공격!, 플레이어 방어 성공!" );
            }
            else
            {
                int CurHp = mPlayer->GetHp() - randAttack;
                CurHp = CurHp < 0 ? 0 : CurHp;
                mPlayer->SetHp(CurHp);

                int randIdx = 0;
                if (mMonster->GetName() == "Boss") 
                    randIdx = RandRange(17, 19);//%( max - min)+ min;
                else
                    randIdx = RandRange(4, 6);
                
                GET_SINGLE(SoundMgr)->PlayEffect(randIdx);

                OutputMsg("       몬스터 공격!, 플레이어 " + to_string(randAttack) + "의 데미지를 입다.");
            }
            SetSubState(mSubState + 1);
        }break;
        case 1:
            mBattleTime += GetDeltaTime();
            shake.shakeTime -= GetDeltaTime();
            if (0.075f < mBattleTime)
            {
                shake.shakeStr = " ";
                OutputMsg();
                SetSubState(mSubState + 1);
            }
            break;
        case 2:
            mBattleTime += GetDeltaTime();
            shake.shakeTime -= GetDeltaTime();
            if (0.075f < mBattleTime)
            {
                if (0.f >= shake.shakeTime)
                    SetSubState(mSubState + 1);
                else {
                    shake.shakeStr = "";
                    OutputMsg();
                    SetSubState(mSubState - 1);
                }
            }
            break;
        case 3:
            shake.Reset();
            OutputMsg();
            if (0 >= mPlayer->GetHp())
                SetState(BTTSTATE::DIE);
            else
                SetSubState(mSubState + 1);
            break;
        case 4:
            mBattleTime += GetDeltaTime();
            if (1.f < mBattleTime)
                NextGameTurn();
            break;
    }  
}

void BattleManager::PlayerWin()
{
    switch (mSubState)
    {
        case 0:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            CleanScreen();
            InputMsg(" ");
            InputMsg(" ");
            OutputMsg("            ====== 플레이어 승리!! ======" );
            SetSubState(mSubState + 1);
        }break;
        case 1:
        {
            mBattleTime += GetDeltaTime();
            if (1.0f > mBattleTime)
                return;
            int randItem = RandRange(0,100); //30%
            if (randItem <= 30)
            {
                int item = DropItem();
                string str = 1 == item ? "HealthPotion" : "attackBoost";
                OutputMsg("          ====== "+ str +" 획득!====== ");
            }
            SetSubState(mSubState + 1);
        }break;
        case 2:
        {
            mBattleTime += GetDeltaTime();
            if (0.5f > mBattleTime)
                return;
            int Gold = mPlayer->GetGold()+ RandRange(1,2)*10;
            mPlayer->SetGold(Gold);
            OutputMsg("           ======  GOLD /" + to_string(Gold) + " 획득!  ====== ");
            SetSubState(mSubState + 1);
        }break;
        case 3:
        {
            mBattleTime += GetDeltaTime();
            if (0.5f > mBattleTime)
                return;
            int Exp = 100;//50;//RandRange(10, 100);
            bool IsLevelUp = mPlayer->SetExperience(Exp);
            if(!IsLevelUp)
                OutputMsg("           ====== 경험치/" + to_string(Exp) + " 획득! ====== ");
            else {
                int level = mPlayer->GetLevel();
                InputMsg("           ====== 경험치/" + to_string(Exp) + " 획득! ====== ");
                OutputMsg("        ====== Level Up!! 현재 레벨:" + to_string(level)+" ====== ");
            }

            SetSubState(mSubState + 1);
        }break;
        case 4:
            mBattleTime += GetDeltaTime();
            if (1.2f > mBattleTime)
                return;
            SetState(BTTSTATE::CLOSE);
            break;
    }
}

void BattleManager::PlayerDie()
{
    switch (mSubState)
    {
        case 0:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            CleanScreen();
            InputMsg(" ");
            InputMsg(" ");
            OutputMsg("           ====== 플레이어 죽다.====== ");
            SetSubState(mSubState + 1);
        }break;
        case 1:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            InputMsg(" ");
            OutputMsg("             ====== GAME OVER ======" );
            SetState(BTTSTATE::CLOSE);
        }break;
    }
}

void BattleManager::SHOP()
{
    switch (mSubState)
    {
    case 0:
    {
        //load Store
        mBattleTime += GetDeltaTime();
        if (0.1f > mBattleTime)
            return;
        SetSubState(mSubState + 1);
    }break;
    case 1:
    {
        int selectstore;

        std::cout << "you arrived the shop, 1 is buyitem, 2 is sellitem" << endl;
        cin >> selectstore;

        if (selectstore == 1)
        {
            int a;
            mShop->DisplayItems();
            cin >> a;
            mShop->BuyItem(a - 1, *mPlayer);

        }
        else if (selectstore == 2)
        {
            std::cout << "sell the item" << endl;
            int b;
            mPlayer->GetInventory().DisplayInventory();
            cin >> b;
            mShop->SellItems(b - 1, *mPlayer);

        }
        SetSubState(mSubState + 1);
    }break;
    }
}

void BattleManager::Status()
{
    switch (mSubState)
    {
        case 0:
        {
            mPlayer->DisplayStatus();
            SetSubState(mSubState + 1);
        }break;
        case 1:

            break;
    }
}

void BattleManager::SetSubState(int subSt)
{
    mBattleTime = 0.f;
    mSubState = subSt;
}

void BattleManager::NextGameTurn()
{
    BTTSTATE St = mGameState == BTTSTATE::MONSTER ? BTTSTATE::PLAYER : BTTSTATE::MONSTER;
    SetState(St);
}

void BattleManager::OutputMsg( string str, bool isNewPage )
{
    std::cout << "\033[H";
    system("cls");
    if (isNewPage)
    {
        mStrArr.clear();
        return;
    }
    if (BTTSTATE::WIN <= mGameState|| mMonster->GetMonsterHp() <= 0)//mMonster->GetMonsterHp() <= 0
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
        std::cout << mMonster->GetAsciiArtDeath() << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
    }
    else if (BTTSTATE::PLAYER == mGameState && shake.shakeTime < 1.f )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_RED);
        std::cout << mMonster->GetAsciiArt() << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
    }
    else
    {
        std::cout << mMonster->GetAsciiArt() << endl;
    }

    if (str != "")
         mStrArr.push_back(str);

    size_t lineMax = 10;
    int lineOver = mStrArr.size() - lineMax;

    for (int i = 0; i < lineOver;++i)
        mStrArr.pop_front(); //erase(mStrArr.begin());

    for (int i = 0; i < mStrArr.size();++i)
        std::cout << mStrArr[i] << endl;

    size_t lineAdd = lineMax - mStrArr.size();
    for (int i = 0; i < lineAdd;++i)
        std::cout << "\n";

    std::cout << "\n";
    if (BTTSTATE::MONSTER == mGameState && shake.shakeTime < 1.f ) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_RED);
        std::cout << shake.shakeStr + "========= 아이템 사용 버튼 HealPotion:1/AttackBoost:2 ==" << endl;
        std::cout << shake.shakeStr + "========================================================" << endl;
        if (mMonster)//BTTSTATE::PLAYER >= mGameState
        {
            std::cout << " NAME:" << mPlayer->GetName() << " HP:" << mPlayer->GetMaxHp() << '/' << mPlayer->GetHp() <<
                " GOLD:" << mPlayer->GetGold() << " Lv:" << mPlayer->GetLevel() << " || " << mMonster->GetName() << " HP:" << mMonster->GetMonsterHp() << endl;
        }
        else
            std::cout << "Name:" << mPlayer->GetName() << " HP:" << mPlayer->GetMaxHp() << '/' << mPlayer->GetHp() << " Gold:" << mPlayer->GetGold() << endl;

        std::cout << shake.shakeStr + "========================================================" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
    }
    else 
    {
        std::cout << shake.shakeStr + "========= 아이템 사용 버튼 HealPotion:1/AttackBoost:2 ==" << endl;
        std::cout << shake.shakeStr + "========================================================" << endl;
        if (mMonster)//BTTSTATE::PLAYER >= mGameState
        {
            std::cout << " NAME:" << mPlayer->GetName() << " HP:" << mPlayer->GetMaxHp() << '/' << mPlayer->GetHp() <<
                " GOLD:" << mPlayer->GetGold() << " Lv:" << mPlayer->GetLevel()<<" || "<< mMonster->GetName() << " HP:" << mMonster->GetMonsterHp() << endl;
        }
        else
            std::cout << "Name:" << mPlayer->GetName() << " HP:" << mPlayer->GetMaxHp() << '/' << mPlayer->GetHp() << " Gold:" << mPlayer->GetGold() << endl;

        std::cout << shake.shakeStr + "========================================================" << endl;
    }
}

void BattleManager::InputMsg(string str)
{
    if (str == "")
        return;
    mStrArr.push_back(str);
}

int BattleManager::RandRange(int min, int max)
{
    srand(time(NULL));
    int RandValue = rand() %( max - min)+ min;
    return RandValue;
}

void BattleManager::CleanScreen()
{
    OutputMsg("",true);
}

int BattleManager::DropItem()
{
    random_device rd;
    mt19937 gen(rd());
    int ItemType = 0;
    uniform_int_distribution<> ItemDist(1, 2);
    ItemType = ItemDist(gen);

    shared_ptr<Item> DroppedItem;
    if (ItemType == 1)
        DroppedItem = make_shared<HealthPotion>(10, 50);

    else if (ItemType == 2)
        DroppedItem = make_shared<AttackBoost>(20, 10);

    mPlayer->AddItem(DroppedItem);

    return ItemType;
}

void BattleManager::Timer()
{
    QueryPerformanceCounter(&cur); // 현재틱
    deltaTime = (cur.QuadPart - prevFrame.QuadPart) / static_cast<float>(frequency.QuadPart);
    //Time += deltaTime;
    prevFrame = cur; // 이전틱 현재틱으로 변경
    // 프레임 구하기
    ++fpsCounter;
    fpsTime += deltaTime;
    if (fpsTime >= 1.0f) // 1초가 지났다면
    {
        fps = fpsCounter; // 프레임
        fpsCounter = 0;
        fpsTime = 0.0f;
    }
    //std::cout << "프레임 :" << fps << " " << "현재시간 : ";
    //std::cout << Time << std::endl;
}
float BattleManager::GetDeltaTime()
{
    return deltaTime;
}



