#pragma once
#include <vector>
#include "obj.h"

#define lpBulletMng Bullet::GetInstance()

class Bullet
{
public:
	static Bullet& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Bullet();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	

	void AddBulletQue(VECTOR pos, UNIT_ID unitid);

private:
	Bullet();
	~Bullet();

	static Bullet* sInstance;

	VECTOR _pos;

	//std::vector<VECTORD> _BulletList;	//íeä€ÉLÉÖÅ[
};

