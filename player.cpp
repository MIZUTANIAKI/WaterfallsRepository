#include <DxLib.h>
#include "scene/SceneMng.h"
#include "player.h"

Player::Player()
{
	_unitID=UNIT_ID::PLAYER;
	_pos = VGet(200.0f, -100.0f, 200.0f);	//ﾌﾟﾚｲﾔ座標初期化

	moveVec = VGet(0.0f, 0.0f, 0.0f);
	movePos = VGet(0.0f, 5000.0f, 0.0f);	//操作軸の座標初期化
	moveYAngle = 0.0f;	//操作軸の角度初期化
	moveXAngle = DX_PI_F;

	playerobj = MV1LoadModel("mv/pShip.mv1"); 
	skyobj = MV1LoadModel("mv/sora.mv1");
	kazi = NULL;
	_flag = true;

	_flagcon = 10;

	fKeyold = false;

	oneCount = GetNowCount();
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

	MV1SetPosition(playerobj, VGet(0.0f, 0.0f, 0.0f));	//ﾌﾟﾚｲﾔ座標変更

	MV1SetRotationXYZ(playerobj, VGet(0.0f, -moveYAngle / 180.0f * DX_PI_F, 0.0f));	//ﾌﾟﾚｲﾔの向きを変更

	MV1SetPosition(playerobj, _pos);	//ﾌﾟﾚｲﾔ座標変更
	MV1SetPosition(skyobj, _pos);	//ﾌﾟﾚｲﾔ座標変更

	lpSceneMng.AddDrawQue(playerobj);	//ﾌﾟﾚｲﾔ描画要求
	lpSceneMng.AddDrawQue(skyobj);	//描画要求

	fKeyold = CheckHitKey(KEY_INPUT_F);
}

void Player::MoveControl(void)
{

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
			moveYAngle += 0.1f;
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
			moveYAngle -= 0.1f;
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
	VECTOR tempCameraPos;
	VECTOR TempMoveVector;
	float  tempf1;
	float  tempf2;
	float  temp1;
	float  temp2;

	tempCameraPos = _pos;	//操作軸の位置をﾌﾟﾚｲﾔ座標で初期化

	//操作軸の高さの角度を求める
	tempf1 = static_cast<float>(sin(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = tempf1 * MOVE_DISTANCE;
	tempPos1.z = -tempf2 * MOVE_DISTANCE;

	//操作軸の横の角度を求める
	tempf1 = static_cast<float>(sin(moveYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(moveYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = tempf2 * tempPos1.x - tempf1 * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = tempf1 * tempPos1.x + tempf2 * tempPos1.z;

	movePos = VAdd(tempPos2, tempCameraPos);


	temp1 = static_cast<float>(sin(static_cast<double>(moveYAngle / 180.0f)* DX_PI_F));
	temp2 = static_cast<float>(cos(static_cast<double>(moveYAngle / 180.0f)* DX_PI_F));

	TempMoveVector.x = moveVec.x * temp2 - moveVec.z * temp1;

	TempMoveVector.y = moveVec.y;

	TempMoveVector.z = moveVec.x * temp1 + moveVec.z * temp2;

	moveVec = VGet(0.0f, 0.0f, 0.0f);

	_pos = VAdd(_pos, TempMoveVector);

}
