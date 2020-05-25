#include<DxLib.h>
#include "objmnj.h"

Objmnj* Objmnj::sInstance = nullptr;


void Objmnj::Setobjpos(VECTOR pos, UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER==id)
	{
		MV1SetPosition(playerobj, pos);
		MV1SetPosition(skyobj, pos);
	}
	if (UNIT_ID::CPU == id)
	{
		MV1SetPosition(enemyobj, pos);
	}
	if (UNIT_ID::BULLET == id)
	{
		MV1SetPosition(bulletmodel[num], pos);
	}
}

int Objmnj::Getobjpos(VECTOR pos, UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		return playerobj;
	}
	if (UNIT_ID::CPU == id)
	{
		return enemyobj;
	}
	if (UNIT_ID::BULLET == id)
	{
		return bulletmodel[num];
	}
}

bool Objmnj::CheckHit(UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		return playerobj;
	}
	if (UNIT_ID::CPU == id)
	{
		return enemyobj;
	}
	if (UNIT_ID::BULLET == id)
	{
		return bulletmodel[num];
	}
	}

Objmnj::Objmnj()
{
	playerobj = MV1LoadModel("mv/pShip.mv1");
	skyobj = MV1LoadModel("mv/sora.mv1");
	enemyobj = MV1LoadModel("mv/eShip.mv1");

	bulletobj = MV1LoadModel("mv/bullet.mv1");
	for (int i = 0; i < BULLETMAX; i++)
	{
		bulletmodel[i] = MV1DuplicateModel(bulletobj);
	}
}

Objmnj::~Objmnj()
{
}

