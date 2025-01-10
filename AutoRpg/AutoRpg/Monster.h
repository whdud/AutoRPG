#pragma once
class Moster
{
public:
	static Moster& GetInstance()
	{
		static Moster m;
		return m;
	}
	Moster();
	~Moster();
};