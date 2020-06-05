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

void Objmnj::ObjDraw(UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		lpSceneMng.AddDrawQue(playerobj);
		lpSceneMng.AddDrawQue(skyobj);
		lpSceneMng.AddDrawQuenex(mapmodel);	//�`��v��
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

	enemyobj = MV1LoadModel("mv/pShip.mv1");
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
void Objmnj::ObjCollHit(VECTOR pos, VECTOR* moveVec, UNIT_ID id)
{
	//MV1RefreshCollInfo(playerobj, -1);
	//MV1RefreshCollInfo(enemyobj, -1);
	//MV1_COLL_RESULT_POLY_DIM hit1;
	//MV1_COLL_RESULT_POLY_DIM hit2;

	//VECTOR tmppos1, tmppos2;
	//tmppos1 = ppos;
	//tmppos2 = ppos;

	//MV1CollCheck_Capsule�������Ȃ��H�H�H0�������Ă�H�H�H�G���[�ŗ�����I�I

	//hit1 = MV1CollCheck_Capsule(enemyobj, -1, tmppos1, tmppos2, 100.0f);

	//�����蔻����̌�n��
	//MV1CollResultPolyDimTerminate(hit1);
}

	//MV1RefreshCollInfo(playerobj, -1);
	//MV1RefreshCollInfo(enemyobj, -1);

	//VECTOR tmppos;
	//VECTOR ChkChToChVec;
	//VECTOR PushVec;
	//VECTOR checkPos;
	//float Length;
	//int hitnum = 0;

	//MV1_COLL_RESULT_POLY_DIM pHit;
	//MV1_COLL_RESULT_POLY_DIM eHit;

	//// �ړ���� ch �̍��W���Z�o
	//checkPos = VAdd(pos, *moveVec);

	////if (UNIT_ID::PLAYER == id)
	//{
	//	tmppos = VAdd(ppos,pvec);
	//	VECTOR tmpevek = ppos;
	//	tmpevek.y = 100.0f;

	//	pHit = MV1CollCheck_Capsule(enemyobj, -1, tmppos, tmpevek, 100.0f);

	//	tmppos.x += pvec.x * 1000;
	//	tmppos.z += pvec.z * 1000;
	//	tmpevek.x += pvec.x * 1000*2;
	//	tmpevek.z += pvec.z * 1000*2;
	//	tmpevek.y = 100.0f;

	//	eHit = MV1CollCheck_Capsule(enemyobj, -1, tmppos, tmpevek, 100.0f);

	//	//pHit = MV1CollCheck_Capsule(enemyobj, -1,checkPos, VAdd(checkPos, VGet(0.0f,1000.0f,0.0f)), 1000.0f);
	//	//eHit = MV1CollCheck_Capsule(enemyobj, -1, VAdd(checkPos, tmpevek), VAdd(checkPos, VAdd(tmpevek, VGet(0.0f, 1000.0f, 0.0f))), 1000.0f);

	//	/*if (HitCheck_Capsule_Capsule(
	//		checkPos, VAdd(checkPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
	//		tmppos, VAdd(tmppos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE ||
	//		HitCheck_Capsule_Capsule(
	//		checkPos, VAdd(checkPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
	//		VAdd(tmppos, tmpevek), VAdd(VAdd(tmppos, tmpevek), VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE)
	//	{
	//		hitnum++;
	//	}*/
	//}
	///*else if (UNIT_ID::CPU == id)
	//{
	//	tmppos = VAdd(ppos, pvec);
	//	VECTOR tmpevek;
	//	tmpevek.x = pvec.x * 1000;
	//	tmpevek.z = pvec.z * 1000;
	//	tmpevek.y = 0.0f;


	//	if (HitCheck_Capsule_Capsule(
	//		checkPos, VAdd(checkPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
	//		tmppos, VAdd(tmppos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE ||
	//		HitCheck_Capsule_Capsule(
	//			checkPos, VAdd(checkPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH,
	//			VAdd(tmppos, tmpevek), VAdd(VAdd(tmppos, tmpevek), VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH) == TRUE)
	//	{
	//		hitnum++;
	//	}
	//}
	//else
	//{
	//	return;
	//}*/

	//hitnum = pHit.HitNum+eHit.HitNum;

	//// �������Ă��Ȃ������牽�����Ȃ�
	////if (pHit.Dim->HitFlag != 0)
	//{
	//	while (hitnum >= 1)
	//	{
	//		// �������Ă����� 

	//		hitnum--;
	//	}
	//}
	//// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
	//*moveVec = VSub(checkPos, pos);


	//// �����蔻����̌�n��
	////MV1CollResultPolyDimTerminate(pHit);

