#include<DxLib.h>
#include "Scene/sceneMng.h"
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

void Objmnj::ObjDraw(UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		lpSceneMng.AddDrawQue(playerobj);
		lpSceneMng.AddDrawQue(skyobj);
	}
	if (UNIT_ID::CPU == id)
	{
		lpSceneMng.AddDrawQue(enemyobj);
	}
	if (UNIT_ID::BULLET == id)
	{
		lpSceneMng.AddDrawQue(bulletmodel[num]);
	}
}

void Objmnj::ObjRotation(UNIT_ID id, float moveangle, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		MV1SetRotationXYZ(playerobj, VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
	}
	if (UNIT_ID::CPU == id)
	{
		MV1SetRotationXYZ(enemyobj, VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
	}
	if (UNIT_ID::BULLET == id)
	{
		MV1SetRotationXYZ(bulletmodel[num], VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
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

	MV1SetScale(skyobj, VGet(1.0f, 1.0f, 1.0f));
}

Objmnj::~Objmnj()
{
}

