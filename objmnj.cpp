#include<DxLib.h>
#include "Scene/sceneMng.h"
#include "objmnj.h"

Objmnj* Objmnj::sInstance = nullptr;


void Objmnj::DrawNaw(void)
{
	//通常物をすべて描画後、ガラスなどの透けたいものを描画する
	//一つずつ描画
	for (auto dQue : _drawList)
	{
		DxLib::MV1DrawModel(dQue);
	}
	//すけるのを描画
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	for (auto dQue : _drawListnex)
	{
		DxLib::MV1DrawModel(dQue);
	}
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 180);

}

void Objmnj::ReSetD(void)
{
	_drawList.clear();
	_drawListnex.clear();
}

void Objmnj::Setobjpos(VECTOR pos, VECTOR vec, UNIT_ID id, int num)
{
	if (UNIT_ID::PLAYER==id)
	{	
		if (num != 0)
		{
			DxLib::MV1SetPosition(playerobjsub[num-1], pos);
		}
		else
		{
			DxLib::MV1SetPosition(playerobj, pos);
		}
		DxLib::MV1SetPosition(skyobj, pos);
		DxLib::MV1SetPosition(phitobj, pos);
		DxLib::MV1SetPosition(mapmodel, VAdd(pos,VGet(0.0f,30.0f,0.0f)));
		pvec = vec;
		ppos = pos;		

	}
	if (UNIT_ID::CPU == id)
	{
		DxLib::MV1SetPosition(enemytmodel[num], pos);
		DxLib::MV1SetPosition(ehitobj, pos);
		evec[num] = vec;
		epos[num] = pos;

	}
	if (UNIT_ID::BULLET == id)
	{
		DxLib::MV1SetPosition(bulletmodel[num], pos);
		bvec[num] = vec;
		bpos[num] = pos;
	}
	if (UNIT_ID::NON == id)
	{
		DxLib::MV1SetPosition(mapmodel, VAdd(pos, VGet(0.0f, 30.0f, 0.0f)));
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
		if (num != 0)
		{
			_drawList.emplace_back(playerobjsub[num-1]);
		}
		else
		{
			_drawList.emplace_back(playerobj);
		}
		_drawList.emplace_back(skyobj);
		_drawListnex.emplace_back(mapmodel);
	}
	if (UNIT_ID::CPU == id)
	{
		_drawList.emplace_back(enemytmodel[num]);
		_drawList.emplace_back(issobj);
	}
	if (UNIT_ID::BULLET == id)
	{
		_drawList.emplace_back(bulletmodel[num]);
	}
}

void Objmnj::ObjRotation(UNIT_ID id, float moveangle, int num)
{
	if (UNIT_ID::PLAYER == id)
	{
		if (num != 0)
		{
			DxLib::MV1SetRotationXYZ(playerobjsub[num-1], VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
		}
		else
		{
			DxLib::MV1SetRotationXYZ(playerobj, VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
		}
		DxLib::MV1SetRotationXYZ(phitobj, VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
		for (int i = 0; i < BULLETMAX; i++)
		{
			DxLib::MV1SetRotationXYZ(bulletmodel[i], VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
		}
	}
	if (UNIT_ID::CPU == id)
	{
		DxLib::MV1SetRotationXYZ(enemytmodel[num], VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
		DxLib::MV1SetRotationXYZ(ehitobj, VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
	}
	//if (UNIT_ID::BULLET == id)
	//{
	//	MV1SetRotationXYZ(bulletmodel[num], VGet(0.0f, moveangle / 180.0f * DX_PI_F, 0.0f));
	//}
}

Objmnj::Objmnj()
{
	playerobj = DxLib::MV1LoadModel("mv/vicShip.mv1");
	for (int i = 0; i < 2; i++)
	{
		playerobjsub[i] = DxLib::MV1DuplicateModel(playerobj);
		DxLib::MV1SetupCollInfo(playerobjsub[i], -1, 1, 1, 1);
	}
	phitobj = DxLib::MV1LoadModel("mv/pHIT.mv1");
	issobj = DxLib::MV1LoadModel("mv/iss.mv1");
	DxLib::MV1SetPosition(issobj, VGet(0.0f, 0.0f, 0.0f));
	DxLib::MV1SetupCollInfo(phitobj, -1, 8, 8, 8);
	ppos = VGet(0.0f, 0.0f, 0.0f);
	pvec = VGet(0.0f, 0.0f, 0.0f);

	skyobj = DxLib::MV1LoadModel("mv/sora.mv1");

	//enemyobj = MV1LoadModel(L"mv/vicShip.mv1");
	enemyobj = DxLib::MV1LoadModel("mv/vicShip.mv1");
	ehitobj = DxLib::MV1LoadModel("mv/pHIT.mv1");
	DxLib::MV1SetupCollInfo(ehitobj, -1, 8, 8, 8);


	bulletobj = DxLib::MV1LoadModel("mv/bullets.mv1");
	for (int i = 0; i < BULLETMAX; i++)
	{
		epos[i] = VGet(0.0f, 0.0f, 15000.0f);
		evec[i] = VGet(0.0f, 0.0f, 0.0f);
		DxLib::MV1SetPosition(enemyobj, epos[i]);
		bullet[i] = UNIT_ID::NON;
		bulletmodel[i] = DxLib::MV1DuplicateModel(bulletobj);
		enemytmodel[i] = DxLib::MV1DuplicateModel(enemyobj);
		DxLib::MV1SetupCollInfo(bulletmodel[i], -1, 1, 1, 1);
		bpos[i] = VGet(0.0f, 0.0f, 0.0f);
		bvec[i] = VGet(0.0f, 0.0f, 0.0f);
	}	



	DxLib::MV1SetScale(skyobj, VGet(2.0f, 2.0f, 2.0f));

	player = UNIT_ID::NON;
	enemy = UNIT_ID::NON;

	mapmodel = DxLib::MV1LoadModel("mv/men.mv1");

	DxLib::MV1SetOpacityRate(mapmodel, 0.5f);

	DxLib::MV1SetScale(mapmodel, VGet(2.5f, 1.1f, 2.5f));
}

Objmnj::~Objmnj()
{
}

bool Objmnj::ObjCollHit(VECTOR pos, UNIT_ID id)
{
	if (id == UNIT_ID::PLAYER)
	{
		//MV1_COLL_RESULT_POLY_DIM HitPolyDim = MV1CollCheck_Sphere(ehitobj, -1, pos, 100.0f);

		//CapsulePos1 = VGet(0.0f, 0.0f, 1050.0f);
		//CapsulePos2 = VGet(0.0f, 0.0f + 200, 1050.0f);
		//MV1_COLL_RESULT_POLY_DIM HitPolyDim = MV1CollCheck_Sphere(ehitobj, -1, pos, 100.0f);

		int hcon = 0;
		for (int i = 0; i < BULLETMAX; i++)
		{

			double tf = ((epos[i].x - pos.x) * (epos[i].x - pos.x)) + ((epos[i].y - pos.y) * (epos[i].y - pos.y)) + ((epos[i].z - pos.z) * (epos[i].z - pos.z));


			double es = 45 * 5, bs = 36 * 14;

			if ((es + bs) >= sqrt(tf))
			{
				hcon++;
			}

		}
		if (hcon != 0)
		{
			return true;
		}
		//VECTOR v1, v2;
		//v1 = pos;
		//v2 = epos;

		//float x, y, z;
		//x = v2.x - v1.x;
		//y = v2.y - v1.y;
		//z = v2.z - v1.z;
		////if (x * x + y * y + z * z <= (50 * 50) * (50 * 50))
		////{
		////	return false;
		////}
		////x = v2.x - v1.x;
		////y = v2.y - v1.y;
		////z = v2.z - v1.z;
		//if (x * x + y * y + z * z <= (50 * 50) * (50 * 50))
		//{
		//	return false;
		//}
		//return true;

		//if (HitPolyDim.HitNum >= 1)
		//{
		//	// 当たった場合は衝突の情報を描画する

		//	// 当たったポリゴンの数を描画
		//	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), L"Hit Poly Num   %d", HitPolyDim.HitNum);

		//	// 当たったポリゴンの数だけ繰り返し
		//	for (int i = 0; i < HitPolyDim.HitNum; i++)
		//	{
		//		// 当たったポリゴンを描画
		//		DrawTriangle3D(
		//			HitPolyDim.Dim[i].Position[0],
		//			HitPolyDim.Dim[i].Position[1],
		//			HitPolyDim.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
		//	}
		//}
		//MV1CollResultPolyDimTerminate(HitPolyDim);
	}
	if (id == UNIT_ID::CPU)
	{
		int hcon = 0;
		for (int i = 0; i < BULLETMAX; i++)
		{

			double tf = ((pos.x - bpos[i].x) * (pos.x - bpos[i].x)) + ((pos.y - bpos[i].y) * (pos.y - bpos[i].y)) + ((pos.z - bpos[i].z) * (pos.z - bpos[i].z));

			double es = 45 * 5, bs = 36 * 14;

			if ((es + bs) >= sqrt(tf))
			{
				hcon++;
			}

		}
		if (hcon != 0)
		{
			return true;
		}
	}
	return false;
}


//if (lpSceneMng.GetFcon() / 60 == 0)
//{
//	return false;
//}
//int Add, i;
//VECTOR CapsulePos1, CapsulePos2;
//VECTOR v1;
//v1 = ppos;
//
//CapsulePos1 = VGet(v1.x, 0.0f, v1.z);
//
//v1.x += moveVec_->x * 20;
//v1.z += moveVec_->z * 20;
//
//CapsulePos2 = VGet(v1.x, 100.0f, v1.z);
//
//
//MV1_COLL_RESULT_POLY_DIM HitPolyDim = MV1CollCheck_Capsule(ehitobj, -1, CapsulePos1, CapsulePos2, 100.0f);
//
//if (HitPolyDim.HitNum >= 1)
//{
//	MV1CollResultPolyDimTerminate(HitPolyDim);
//	return false;
//}
//
//// 当たり判定情報の後始末
//MV1CollResultPolyDimTerminate(HitPolyDim);
//return false;





// 当たり判定を行う球の位置をセット
	//CapsulePos1 = VGet(0.0f, 0.0f, 1050.0f);
	//CapsulePos2 = VGet(0.0f, 0.0f + 200, 1050.0f);
	//hit1 = MV1CollCheck_Capsule(enemyobj, -1, CapsulePos1, CapsulePos2, 100.0f);
	// モデルとカプセルとの当たり判定
	////球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
	////球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
	////(x2 - x1) ^ 2 + (y2 - y1) ^ 2 + (z2 - z1) ^ 2 <= (r1 + r2) ^ 2ならば衝突を起こしている
	//VECTOR v1, v2, mv;
	//v1 = ppos;
	//v2 = epos;
	//mv = pvec;
	//float x, y, z;
	//x = v2.x - v1.x;
	//y = v2.y - v1.y;
	//z = v2.z - v1.z;
	//if (x * x + y * y + z * z <= (50 * 50) * (50 * 50))
	//{
	//	return false;
	//}x = v2.x - v1.x + (mv.x * 5000);
	//y = v2.y - v1.y;
	//z = v2.z - v1.z + (mv.z * 5000);
	//if (x * x + y * y + z * z <= (50 * 50) * (50 * 50))
	//{
	//	return false;
	//}
	//
	//return true;



//MV1RefreshCollInfo(playerobj, -1);
	//MV1RefreshCollInfo(enemyobj, -1);
	//MV1_COLL_RESULT_POLY_DIM hit1;
	//MV1_COLL_RESULT_POLY_DIM hit2;

	//VECTOR tmppos1, tmppos2;
	//tmppos1 = ppos;
	//tmppos2 = ppos;

	//hit1 = MV1CollCheck_Capsule(enemyobj, -1, tmppos1, tmppos2, 100.0f);

	//当たり判定情報の後始末
	//MV1CollResultPolyDimTerminate(hit1);
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

	//// 移動後の ch の座標を算出
	//checkPos = VAdd(pos, *moveVec_);

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

	//// 当たっていなかったら何もしない
	////if (pHit.Dim->HitFlag != 0)
	//{
	//	while (hitnum >= 1)
	//	{
	//		// 当たっていたら 

	//		hitnum--;
	//	}
	//}
	//// 当たり判定処理後の移動ベクトルをセット
	//*moveVec_ = VSub(checkPos, pos);


	//// 当たり判定情報の後始末
	////MV1CollResultPolyDimTerminate(pHit);

