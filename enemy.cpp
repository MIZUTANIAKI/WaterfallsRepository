#include <math.h>
#include "Dxlib.h"
#include "scene/SceneMng.h"
#include "Scene/GameScene.h"
#include "Bullet.h"
#include "enemy.h"
#include "objmnj.h"

Enemy::Enemy()
{
	_unitID = UNIT_ID::CPU;
	_pos = VGet(0.0f, 0.0f, 0.0f);	//敵の座標初期化


	moveVec = VGet(1000.0f, 0.0f, -55000.0f);
	movePos = VGet(0.0f, 5000.0f, 0.0f);	//操作軸の座標初期化
	moveYAngle = 180.0f;	//操作軸の角度初期化
	moveXAngle = DX_PI_F;

	_flag = true;

	_flagcon = 10;

	fKeyold = false;

	oneCount = GetNowCount();

	_ppos = VGet(0.0f, 0.0f, 0.0f);

	_State = STATE_ID::STAY;
	_LorR = LORR::NON;
}

Enemy::~Enemy()
{
}

void Enemy::Updata(void)
{

	//向きを変更
	lpobjlMng.ObjRotation(_unitID, -moveYAngle, 0);
	//座標設定
	lpobjlMng.Setobjpos(_pos, moveVec, _unitID, 0);

	//描画に投げる
	lpobjlMng.ObjDraw(_unitID, 0);

	fKeyold = CheckHitKey(KEY_INPUT_F);
}

void Enemy::Updata(VECTOR pos)
{
	if(abs(VSub(_pos, pos).z)<3000.0f&& abs(VSub(_pos, pos).x) < 3000.0f)
	{
		_State = STATE_ID::ACTIVE;

	}
	else
	{
		_State = STATE_ID::STAY;
	}
	_State = STATE_ID::STAY;

	_ppos = pos;
	
	if (CheckHitKey(KEY_INPUT_F))
	{
		if (!fKeyold)
		{
			if (!_flag)
			{
				_flag = true;
			}
			else
			{
				_flag = false;
				_flagcon = 10;
			}
		}
	}

	if (!_flag)
	{
		// １秒たっているか
		if (GetNowCount() - oneCount > 1000)
		{

			_flagcon--;

			oneCount = GetNowCount();
		}


	}

	MoveControl();

	nbullet1.Run();

}

void Enemy::MoveControl(void)
{
	


	if(_State == STATE_ID::STAY)
	{
		
	}
	else if(_State == STATE_ID::ACTIVE)
	{

		//VECTOR tmpcrossvec = VCross(VSub(_pos, movePos), VSub(_pos, _ppos));

		//if (tmpcrossvec.x == 0.0f && tmpcrossvec.z == 0.0f)
		//{
		//	_LorR = LORR::NON;
		//}
		//if (!signbit(tmpcrossvec.x))
		//{
		//	//プラスの場合は、右に
		//	_LorR = LORR::RIGHT;
		//	moveYAngle += 0.1f;
		//	if (moveYAngle >= 180.0f)
		//	{
		//		moveYAngle -= 360.0f;
		//	}
		//}

		//if(!signbit(tmpcrossvec.z))
		//{
		//	//プラスの場合は、右に
		//	_LorR = LORR::RIGHT;
		//	moveYAngle += 0.1f;
		//	if (moveYAngle >= 180.0f)
		//	{
		//		moveYAngle -= 360.0f;
		//	}
		//}
		//
		//if (signbit(tmpcrossvec.x))
		//{
		//	//マイナスの場合は左に
		//	_LorR = LORR::LEFT;
		//	moveYAngle -= 0.1f;
		//	if (moveYAngle <= -180.0f)
		//	{
		//		moveYAngle += 360.0f;
		//	}
		//}
		//if(signbit(tmpcrossvec.z))
		//{
		//	//マイナスの場合は左に
		//	_LorR = LORR::LEFT;
		//	moveYAngle -= 0.1f;
		//	if (moveYAngle <= -180.0f)
		//	{
		//		moveYAngle += 360.0f;
		//	}
		//}

		/*if (_LorR == LORR::RIGHT)
		{
			moveYAngle += 0.1f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle -= 360.0f;
			}

		}
		else if(_LorR == LORR::LEFT)
		{
			moveYAngle -= 0.1f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle += 360.0f;
			}

		}
		else
		{

		}*/

	}
	
	//if ( _pos.x > _ppos.x/*&&  _pos.z > _ppos.z*/)
	//{

	//}

	

	

	if (_flag)
	{
		moveVec.z += 1.0f;
	}
	else
	{
		if (_flagcon >= 8)
		{
			moveVec.z += 4.0f;
		}
		else if (_flagcon >= 6)
		{
			moveVec.z += 3.0f;
		}
		else if (_flagcon >= 4)
		{
			moveVec.z += 2.0f;
		}
		else
		{
			moveVec.z += 1.0f;
		}
	}


	//lpobjlMng.ObjCollHit(_pos, &moveVec, _unitID);

	VECTOR tempPos1;
	VECTOR tempPos2;
	VECTOR tempMovePos;
	VECTOR tempMoveVec;
	float  tempf1;
	float  tempf2;
	float  temp1;
	float  temp2;

	tempMovePos = _pos;	//操作軸の位置をﾌﾟﾚｲﾔ座標で初期化

	//操作軸の高さの角度を求める
	tempf1 = static_cast<float>(sin(1.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(1.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = 0.0f;
	tempPos1.z = -tempf2 * MOVE_DISTANCE;

	//操作軸の横の角度を求める
	tempf1 = static_cast<float>(sin(moveYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(moveYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = tempf2 * tempPos1.x - tempf1 * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = tempf1 * tempPos1.x + tempf2 * tempPos1.z;

	movePos = VAdd(tempPos2, tempMovePos);


	temp1 = static_cast<float>(sin(static_cast<double>(moveYAngle / 180.0f)* DX_PI_F));
	temp2 = static_cast<float>(cos(static_cast<double>(moveYAngle / 180.0f)* DX_PI_F));

	tempMoveVec.x = moveVec.x * temp2 - moveVec.z * temp1;

	tempMoveVec.y = 0.0f;

	tempMoveVec.z = moveVec.x * temp1 + moveVec.z * temp2;

	moveVec = VGet(0.0f, 0.0f, 0.0f);

	_pos = VAdd(_pos, tempMoveVec);

	float tmptmpfl = Segment_Segment_MinLength(_pos, _pos, _ppos, _ppos);

	if (_State == STATE_ID::ACTIVE &&tmptmpfl<1000.0f)/*(abs(VSub(_ppos,_pos ).x) < 1000.0f&& abs(VSub(_ppos, _pos).z) < 1000.0f)*/
	{
		VECTOR tmpvec1 = _pos, tmpvec2 = movePos;

		tmpvec1.y = 0.0f;
		tmpvec2.y = 0.0f;

		nbullet1.SetBullet(VAdd(_pos, VGet(0.0f, 100.0f, 0.0f)), VNorm(VSub(tmpvec1, tmpvec2)));
	}
}
