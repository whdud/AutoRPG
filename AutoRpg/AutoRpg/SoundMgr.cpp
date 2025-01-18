#include "SoundMgr.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h> 
#include <mmsystem.h> // MCI 관련 함수 포함
#pragma comment(lib, "winmm.lib") // winmm.lib 링크

SoundMgr::SoundMgr():
    sNameArr
    {
        "BG0.wav",
        "BG1.wav",
        "BIGCHIKEN_DMA0.wav",
        "BIGCHIKEN_DMA1.wav",
        "PANDAFLY_DAMAGE_0.wav",
        "PANDAFLY_DAMAGE_1.wav",
        "tiger_7.wav",
        "BOX_OPEN.wav",
        "BOX_OPENEFF.wav",
        "CHIKEN_DMG_0.wav",
        "CHIKEN_DMG_1.wav",
        "GOLDCHIKEN_DEATH.wav",
        "PANDA_DEATH1.wav",
        "PANDA_DEATH2.wav",
        "PANDA_DEATH3.wav",
        "PANDA_DEATH0_TEMP.wav",
        "girl_Damege.wav",
        "CHIKEN_CRY.wav",
        "BIGCHIKEN_APPEAR.wav"
    }
{
    //for (int i = 0; i < sizeof(sNameArr) / sizeof(sNameArr[0]);++i)
    //    cout << sNameArr[i] << endl;
}
SoundMgr::~SoundMgr()
{
    int dsfsadf = 0;
}
void SoundMgr::PlayBGM(int idx)
{
    PlayBGM(sNameArr[idx]);
}
void SoundMgr::PlayBGM(const string& bgmFile)
{
    // BGM 트랙 열기 및 재생
    wstring command = L"open \"" + wstring(bgmFile.begin(),bgmFile.end()) + L"\" type mpegvideo alias BGM";
    mciSendString(command.c_str(), NULL, 0, NULL);
    mciSendString(_T("play BGM repeat"), NULL, 0, NULL); // 반복 재생
}

void SoundMgr::PlayEffect(int idx)
{
    PlayEffect(sNameArr[idx], sNameArr[idx]);
}

void SoundMgr::PlayEffect(const string& effectFile, const string& alias)
{
    std::wstring closeCommand = L"close " + std::wstring(alias.begin(), alias.end());
    mciSendString(closeCommand.c_str(), NULL, 0, NULL);

    // 효과음 트랙 열기 및 비동기 재생
    std::wstring openCommand = L"open \"" + wstring(effectFile.begin(),effectFile.end()) + L"\" type mpegvideo alias " + wstring(alias.begin(),alias.end());
    mciSendString(openCommand.c_str(), NULL, 0, NULL);

    std::wstring playCommand = L"play " + wstring(alias.begin(),alias.end());
    mciSendString(playCommand.c_str(), NULL, 0, NULL);
}

void SoundMgr::StopBGM()
{
    mciSendString(_T("stop BGM"), NULL, 0, NULL);
    mciSendString(_T("close BGM"), NULL, 0, NULL);
}

void SoundMgr::StopEffect(const string& alias)
{
    std::wstring stopCommand = L"stop " + std::wstring(alias.begin(),alias.end());
    mciSendString(stopCommand.c_str(), NULL, 0, NULL);

    std::wstring closeCommand = L"close " + std::wstring(alias.begin(), alias.end());
    mciSendString(closeCommand.c_str(), NULL, 0, NULL);
}
SoundMgr* SoundMgr::instance = NULL;