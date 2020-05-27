#include<DxLib.h>
#include "Scene/sceneMng.h"
#include "objmnj.h"

Objmnj* Objmnj::sInstance = nullptr;


void Objmnj::Setobjpos(VECTOR pos, VECTOR vec, UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER==id)
	{
		MV1SetPosition(playerobj, pos);
		MV1SetPosition(skyobj, pos);
		MV1SetPosition(mapmodel, pos);
		pvec = vec;
		ppos = pos;
	}
	if (UNIT_ID::CPU == id)
	{
		MV1SetPosition(enemyobj, pos);
		evec = vec;
		epos = pos;
	}
	if (UNIT_ID::BULLET == id)
	{
		MV1SetPosition(bulletmodel[num], pos);
		bvec[num] = vec;
		bpos[num] = pos;
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
	return false;
}

UNIT_ID Objmnj::CheckHit(UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		return player;
	}
	if (UNIT_ID::CPU == id)
	{
		return enemy;
	}
	if (UNIT_ID::BULLET == id)
	{
		return bullet[num];
	}
	return UNIT_ID::NON;
}

void Objmnj::TryHit(void)
{

}

void Objmnj::ObjDraw(UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		lpSceneMng.AddDrawQue(playerobj);
		lpSceneMng.AddDrawQue(skyobj);
		lpSceneMng.AddDrawQuenex(mapmodel);	//描画要求
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
	playerobj = MV1LoadModel("mv/vicShip.mv1");
	MV1SetupCollInfo(playerobj, -1, 1, 1, 1);

	skyobj = MV1LoadModel("mv/sora.mv1");

	enemyobj = MV1LoadModel("mv/vicShip.mv1");
	MV1SetupCollInfo(enemyobj, -1, 1, 1, 1);

	bulletobj = MV1LoadModel("mv/bullet.mv1");
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i] = UNIT_ID::NON;
		bulletmodel[i] = MV1DuplicateModel(bulletobj);
		MV1SetupCollInfo(bulletmodel[1], -1, 1, 1, 1);
	}

	MV1SetScale(skyobj, VGet(2.0f, 2.0f, 2.0f));

	player = UNIT_ID::NON;
	enemy = UNIT_ID::NON;

	mapmodel = MV1LoadModel("mv/men.mv1");

	MV1SetOpacityRate(mapmodel, 0.5f);

	MV1SetScale(mapmodel, VGet(2.5f, 1.1f, 2.5f));
}

Objmnj::~Objmnj()
{
}

/*, F* */
void Objmnj::ObjCollHit(VECTOR pos, VECTOR* moveVec,UNIT_ID id)
{
	MV1RefreshCollInfo(playerobj, -1);
	MV1RefreshCollInfo(enemyobj, -1);

	VECTOR tmppos;
	VECTOR checkpos;
	int hitnum = 0;


	// 移動後の ch の座標を算出
	checkpos = VAdd(pos, *moveVec);

	//if (UNIT_ID::PLAYER == id)
	{
		tmppos = VAdd(epos,evec);
		VECTOR tmpevek;
		tmpevek.x = evec.x * 200;
		tmpevek.z = evec.z * 200;
		tmpevek.y = 0.0f;

		//pHit = MV1CollCheck_Capsule(playerobj, -1,checkpos, VAdd(tmppos, tmpevek), 100.0f);


		if (HitCheck_Capsule_Capsule(
			checkpos, VAdd(checkpos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
			tmppos, VAdd(tmppos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE ||

			HitCheck_Capsule_Capsule(
				checkpos, VAdd(checkpos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
				VAdd(tmppos, tmpevek), VAdd(VAdd(tmppos, tmpevek), VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE)
		{
			hitnum++;
		}
	}
	/*else if (UNIT_ID::CPU == id)
	{
		tmppos = VAdd(ppos, pvec);
		VECTOR tmpevek;
		tmpevek.x = pvec.x * 1000;
		tmpevek.z = pvec.z * 1000;
		tmpevek.y = 0.0f;


		if (HitCheck_Capsule_Capsule(
			checkpos, VAdd(checkpos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
			tmppos, VAdd(tmppos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE ||
			HitCheck_Capsule_Capsule(
				checkpos, VAdd(checkpos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
				VAdd(tmppos, tmpevek), VAdd(VAdd(tmppos, tmpevek), VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE)
		{
			hitnum++;
		}
	}
	else
	{
		return;
	}*/

	//hitnum = pHit.HitNum;

	// 当たっていなかったら何もしない
	while (hitnum >0)
	{
		// 当たっていたら ch が chk から離れる処理をする

		hitnum--;
	}

	// 当たり判定処理後の移動ベクトルをセット
	*moveVec = VSub(checkpos, pos);


	// 当たり判定情報の後始末
	MV1CollResultPolyDimTerminate(pHit);
}

