#pragma once
#include <iostream>
#include <string>

using namespace std;

class SoundMgr
{
public:
	static SoundMgr* instance ;

public:
	static SoundMgr* GetInstance()
	{
		if (instance == nullptr )
			instance = new SoundMgr();
		return instance;
	}
public: 
	SoundMgr();
	~SoundMgr();
private:
	string sNameArr[19];
public:
	void PlayBGM(int idx);
	void PlayBGM(const string& bgmFile);
	void PlayEffect(int idx);
	void PlayEffect(const string& effectFile, const string& alias);
	void StopBGM();
	void StopEffect(const string& alias);
};

