#include <DxLib.h>
#include "scene/SceneMng.h"
#include "Scene/GameScene.h"
#include "Bullet.h"
#include "player.h"
#include "objmnj.h"

Player::Player()
{
	_unitID=UNIT_ID::PLAYER;
	_pos = VGet(0.0f, 0.0f, 0.0f);	//ﾌﾟﾚｲﾔ座標初期化

	moveVec = VGet(0.0f, 0.0f, 0.0f);
	movePos = VGet(0.0f, 5000.0f, 0.0f);	//操作軸の座標初期化
	moveYAngle = 0.0f;	//操作軸の角度初期化
	moveXAngle = DX_PI_F;

	kazi = NULL;
	_flag = true;

	_flagcon = 10;

	fKeyold = false;

	oneCount = GetNowCount();

	_tmppPos = _pos;
}

Player::~Player()
{
}

void Player::Updata(void)
{
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

	pbullet.Run();

	//ﾌﾟﾚｲﾔの向きを変更
	lpobjlMng.ObjRotation(_unitID, -moveYAngle, 0);
	//座標設定
	lpobjlMng.Setobjpos(_pos, moveVec, _unitID, 0);

	//描画に投げる
	lpobjlMng.ObjDraw(_unitID, 0);

	fKeyold = CheckHitKey(KEY_INPUT_F);

	VECTOR tmpvec = VNorm(VSub(_pos, movePos));
	tmpvec.x *= 2500.0f;
	tmpvec.z *= 2500.0f;
	tmpvec.y = 0;
	_tmppPos = _pos;
	_pos = VAdd(_pos, tmpvec);
}

void Player::MoveControl(void)
{
	_pos = _tmppPos;

	//操作
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (lpSceneMng.GetFcon() % 30 == 0)
		{
			kazi++;
			if (kazi > 10)
			{
				kazi = 10;
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{

		if (lpSceneMng.GetFcon() % 30 == 0)
		{
			kazi--;
			if (kazi < -10)
			{
				kazi = -10;
			}
		}
	}
	else
	{
		if (kazi != NULL)
		{
			if (kazi > 0)
			{
				kazi-=2;
				if (kazi < 0)
				{
					kazi = NULL;
				}
			}
			else if (kazi < 0)
			{
				kazi+=2;
				if (kazi > 0)
				{
					kazi = NULL;
				}
			}
			else
			{
				kazi = NULL;
			}
		}
	}

	if (kazi > 2)
	{
		if (kazi > 6)
		{
			moveYAngle += 0.06f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle -= 360.0f;
			}
		}
		else if (kazi < 6)
		{
			moveYAngle += 0.08f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle -= 360.0f;
			}
		}
		else if (kazi <= 10)
		{
			moveYAngle += 0.12f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle -= 360.0f;
			}
		}
	}

	if (kazi < -2)
	{
		if (kazi < -6)
		{
			moveYAngle -= 0.06f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle += 360.0f;
			}
		}
		else if (kazi > -6)
		{
			moveYAngle -= 0.08f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle += 360.0f;
			}
		}
		else if (kazi >= -10)
		{
			moveYAngle -= 0.12f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle += 360.0f;
			}
		}
	}

	if (_flag)
	{
		moveVec.z += 5.0f;
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


	lpobjlMng.ObjCollHit(_pos, &moveVec,_unitID);

	temp1 = static_cast<float>(sin(static_cast<double>(moveYAngle / 180.0f)* DX_PI_F));
	temp2 = static_cast<float>(cos(static_cast<double>(moveYAngle / 180.0f)* DX_PI_F));

	tempMoveVec.x = moveVec.x * temp2 - moveVec.z * temp1;

	tempMoveVec.y = 0.0f;

	tempMoveVec.z = moveVec.x * temp1 + moveVec.z * temp2;

	moveVec = tempMoveVec;

	_pos = VAdd(_pos,moveVec);

	moveVec = VGet(0.0f, 0.0f, 0.0f);

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		VECTOR tmpvec1= _pos, tmpvec2= movePos;

		tmpvec1.y = 0.0f;
		tmpvec2.y = 0.0f;

		pbullet.SetBullet(VAdd(_pos,VGet(0.0f,100.0f,0.0f)), VNorm(VSub(tmpvec1, tmpvec2)));
	}
}

