#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Shop.h"
#include "Inventory.h"
#include "defines.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>

BattleManager::BattleManager()
{
    QueryPerformanceFrequency(&frequency); // 한번만 읽어들이면 된다.
    QueryPerformanceCounter(&prevFrame); // 이전틱 기억

    mShop = new Shop;
    mInventory = new Inventory;
}

BattleManager::~BattleManager()
{
}

BTTRESULT BattleManager::Update( Character* player)
{
    mPlayer = player;
    Timer();
    //cout << "\033[H";
    switch (mGameState) {
        case BTTSTATE::EMPTY:
            //ReadyBattle();
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
        case BTTSTATE::STORE:
            Store();
            break;
        case BTTSTATE::STATUS:
            Status();
            break;
        case BTTSTATE::CLOSE:
            Close();
            break;
    }

    KeyButton();

    if (mGameState == BTTSTATE::EMPTY) // Start Delay or Next Game
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
                UseItem(0);
            else if (input == '2')
                UseItem(1);
        }
        else if (BTTSTATE::CLOSE == mGameState)
        {
            if (CLOSESTATE::cDIE == mSubState)//ReStartGame:A / OutGame:Q 
            {
                if (input == 'a')//
                {
                    mPlayer->ResetCharacter();
                    SetState(BTTSTATE::EMPTY);
                }
                else if (input == 'q')
                    exit(0);
            }
            else// CLOSESTATE::WIN  // Store:A /Mob hunting:S / Status:D 
            {
                if (input == 'a')//
                    SetState(BTTSTATE::STORE);
                else if (input == 's')
                    SetState(BTTSTATE::EMPTY);
                else if (input == 'd')
                    SetState(BTTSTATE::STATUS);
            }
        }
        else if (BTTSTATE::STORE)
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
                //mMonster->GetMonsterHp() = 10;//temp
                CleanScreen();
                InputMsg("  ");
                InputMsg("  ");
                InputMsg("  ");
                OutputMsg("         ========== BATTLE START ==========");
                SetSubState(mSubState+1);
            }
            break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (1.f < mBattleTime)
            {
                CleanScreen();
                if (mMonster->GetName() == "Boss")
                {
                    InputMsg ("              ========================= ");
                    InputMsg("    ========== BOSS가 등장 하였습니다! ==========");
                    OutputMsg("              =========================");
                }
                BTTSTATE St = BTTSTATE( RandRange(2,2) );
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
                if (BTTSTATE::STORE == mPrvGameState || BTTSTATE::STATUS == mPrvGameState)
                    CleanScreen();

                if ("Boss" == mMonster->GetName()) 
                {
                    InputMsg(" ");
                    InputMsg(" ");
                    InputMsg("            ======  전투 종료  ======");
                    InputMsg(" ");
                    InputMsg("        축하합니다! 게임 엔딩을 보셨습니다!");
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
        exit(0);
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
 
void BattleManager::UseItem(int item)
{
    if (0 == item) //inventory
    {
        bool isItem = mPlayer->IsHealthPotion();
        if (isItem)
        {
            mPlayer->UseItem(0);
            OutputMsg("        Use Item Hp +5!!");
        }
        else
            OutputMsg("        Error! Empty Item!!");
    }
    else if (1 == item) //inventory
    {
        bool isItem = mPlayer->IsAttackBoost();
        if (isItem)
        {
            mPlayer->UseItem(1);
            OutputMsg("        Use Item AttackBoost!!");
        }
        else
            OutputMsg("        Error! Empty Item!!");
    }
}

void BattleManager::PlayerTurn()
{
    switch (mSubState)
    {
        case 0:
        {
            if (0 >= mPlayer->GetHp())
            {
                SetState(BTTSTATE::DIE);
                return;
            }
            
            int randAttack = mPlayer->GetAttack()+ RandRange(0, 5);
           
            if (randAttack == 0)
                OutputMsg("     플레이어 공격!, 몬스터 방어 성공!");
            else
            {
                mMonster->TakeDamage(randAttack);
                OutputMsg("     플레이어 공격!, 몬스터 " + to_string(randAttack) + "의 데미지를 입다.");
            }
            SetSubState(mSubState + 1);
        }break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (1.5f < mBattleTime)
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
            if (0 == mMonster->GetMonsterHp() )
            {
                SetState(BTTSTATE::WIN);
                return;
            }

            int randAttack = RandRange(0, 5);
            if (randAttack == 0) 
                OutputMsg("     몬스터 공격!, 플레이어 방어 성공!");
            else
            {
                int CurHp = mPlayer->GetHp() - randAttack;
                CurHp = CurHp < 0 ? 0 : CurHp;
                mPlayer->SetHp(CurHp);

                OutputMsg("     몬스터 공격!, 플레이어 " + to_string(randAttack) + "의 데미지를 입다.");
            }
            SetSubState(mSubState + 1);
        }break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (1.5f < mBattleTime)
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
            if (randItem <= 33)
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

void BattleManager::Store()
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

        cout << "you arrived the shop, 1 is buyitem, 2 is sellitem" << endl;
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
            cout << "sell the item" << endl;
            int b;
            mPlayer->GetInventory().DisplayInventory();
            cin >> b;
            mShop->SellItems(b - 1, *mPlayer);

        }
        //int HealthPotion = 5;//Load Shop!
        //int attackBoost = 5;//Load Shop!
        //CleanScreen();
        //InputMsg("       ====================================== ");
        //InputMsg("     ==                                      == ");
        //InputMsg("  ==================== 상점 ====================== ");
        //InputMsg(" ");
        //InputMsg("                ====== 구매 ======");
        //InputMsg("    ==== HealthPotion : A / AttackBoost : S ====");
        //InputMsg(" ");

        //InputMsg("           ====  보유 아이템 목록  ====");
        //InputMsg("        HealthPotion: " + to_string(HealthPotion) + " 개" + " attackBoost: " + to_string(attackBoost) + " 개");
        //InputMsg(" ");
     
        //OutputMsg("                              === 돌아가기: q ===");
       

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
    //cout << "\033[H";
    system("cls");
    if (isNewPage)
    {
        mStrArr.clear();
       // cout << "CLSCLSCLSCLSCLSCLSCLSCLSCLSCLSCLSCLSCLSCLSCLS"<<endl;
        return;
    }
    if (str == "")
        return;
    cout << mMonster->GetAsciiArt() << endl;

    mStrArr.push_back(str);

    size_t lineMax = 10;
    int lineOver = mStrArr.size() - lineMax;

    for (int i = 0; i < lineOver;++i)
        mStrArr.erase(mStrArr.begin());

    for (int i = 0; i < mStrArr.size();++i)
        cout << mStrArr[i] << endl;

    size_t lineAdd = lineMax - mStrArr.size();
    for (int i = 0; i < lineAdd;++i)
        cout << "\n";

    cout << "                                                        " << endl;
    cout << "========= 아이템 사용 버튼 HealPotion:1/AttackBoost:2 ==" << endl;
    cout << "========================================================" << endl;
    if (mMonster)//BTTSTATE::PLAYER >= mGameState
    {
        cout << " NAME:" << mPlayer->GetName() << " HP:" << mPlayer->GetMaxHp() << '/' << mPlayer->GetHp() <<
            " GOLD:" << mPlayer->GetGold() << " Lv:" << mPlayer->GetLevel()<<" || "<< mMonster->GetName() << " HP:" << mMonster->GetMonsterHp() << endl;
    }
    else
    {
        cout << "Name:" << mPlayer->GetName() << " HP:" << mPlayer->GetMaxHp() << '/' << mPlayer->GetHp() << " Gold:" << mPlayer->GetGold() << endl;
    }
    cout << "========================================================" << endl;
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
    int RandValue = rand() % max + min;
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



