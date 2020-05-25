#pragma once
#define CPU_MAX 2
#include "obj.h"


#define BULLETMAX 2
#define lpobjlMng Objmnj::GetInstance()

class Objmnj
{
public:
	static Objmnj& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Objmnj();
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

	void Setobjpos(VECTOR pos, UNIT_ID id, int num);

	int Getobjpos(VECTOR pos, UNIT_ID id, int num);

	bool CheckHit(UNIT_ID id, int num);

	void ObjDraw(UNIT_ID id, int num);

	void ObjRotation(UNIT_ID id,float moveangle, int num);

private:
	static Objmnj* sInstance;

	int		playerobj;			//ÌßÚ²Ôƒ‚ƒfƒ‹Ši”[—p
	int		skyobj;				//‹ó
	int		enemyobj;			//“Gƒ‚ƒfƒ‹Ši”[—p
	int		bulletobj;			//
	int		bulletmodel[BULLETMAX];

	Objmnj();
	~Objmnj();
};

