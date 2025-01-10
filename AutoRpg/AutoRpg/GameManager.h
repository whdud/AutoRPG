#pragma once
class GameManger
{
public:
	static GameManger& GetInstance()
	{
		static GameManger gm;
		return gm;
	}


	GameManger();
	~GameManger();

private:

};



