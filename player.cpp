#include <DxLib.h>
#include "scene/SceneMng.h"
#include "player.h"

Player::Player()
{
	_pos = VGet(200.0f, -100.0f, 200.0f);	//ﾌﾟﾚｲﾔ座標初期化

	moveVec = VGet(0.0f, 0.0f, 0.0f);
	movePos = VGet(0.0f, 5000.0f, 0.0f);	//操作軸の座標初期化
	moveYAngle = 0.0f;	//操作軸の角度初期化
	moveXAngle = DX_PI_F;

	playerobj = MV1LoadModel("mv/p.x"); 
	skyobj = MV1LoadModel("mv/sora.mv1");
	kazi = NULL;
	cameraInit();
}

Player::~Player()
{
}

void Player::Updata(void)
{



	
	MoveControl();

	MV1SetPosition(playerobj, VGet(0.0f, -100.0f, 0.0f));	//ﾌﾟﾚｲﾔ座標変更


	MV1SetPosition(playerobj, _pos);	//ﾌﾟﾚｲﾔ座標変更
	MV1SetPosition(skyobj, _pos);	//ﾌﾟﾚｲﾔ座標変更


	lpSceneMng.AddDrawQue(playerobj);	//ﾌﾟﾚｲﾔ描画要求
	lpSceneMng.AddDrawQue(skyobj);	//描画要求
}

void Player::MoveControl(void)
{

	//カメラの操作
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
	//else
	//{
	//	if (kazi != NULL)
	//	{
	//		if (kazi > 0)
	//		{
	//			kazi-=2;
	//			if (kazi < 0)
	//			{
	//				kazi = NULL;
	//			}
	//		}
	//		else if (kazi < 0)
	//		{
	//			kazi+=2;
	//			if (kazi > 0)
	//			{
	//				kazi = NULL;
	//			}
	//		}
	//		else
	//		{
	//			kazi = NULL;
	//		}
	//	}
	//}

	if (kazi > 2)
	{
		if (kazi < 4)
		{
			moveYAngle += 0.05f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle = -360.0f;
			}
		}
		else if (kazi < 6)
		{
			moveYAngle += 0.055f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle = -360.0f;
			}
		}
		else if (kazi < 8)
		{
			moveYAngle += 0.551f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle = -360.0f;
			}
		}
		else if (kazi <= 10)
		{
			moveYAngle += 0.5512f;
			if (moveYAngle >= 180.0f)
			{
				moveYAngle = -360.0f;
			}
		}
	}

	if (kazi < -2)
	{
		if (kazi > -4)
		{
			moveYAngle -= 0.05f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle = 360.0f;
			}
		}
		else if (kazi > -6)
		{
			moveYAngle -= 0.08f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle = 360.0f;
			}
		}
		else if (kazi > -8)
		{
			moveYAngle -= 1.0f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle = 360.0f;
			}
		}
		else if (kazi >= -10)
		{
			moveYAngle -= 1.5f;
			if (moveYAngle <= -180.0f)
			{
				moveYAngle = 360.0f;
			}
		}
	}

	moveVec.z += 1.0f;


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
	tempPos1.y = tempf1 * CAMERA_DISTANCE;
	tempPos1.z = -tempf2 * CAMERA_DISTANCE;

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

void Player::cameraInit(void)
{
	SetCameraNearFar(100.0f, 100.0f);
}
