#include <DxLib.h>
#include "scene/SceneMng.h"
#include "player.h"

Player::Player()
{
	_unitID=UNIT_ID::PLAYER;
	_pos = VGet(200.0f, -100.0f, 200.0f);	//ΜίΪ²ΤΐWϊ»

	moveVec = VGet(0.0f, 0.0f, 0.0f);
	movePos = VGet(0.0f, 5000.0f, 0.0f);	//μ²ΜΐWϊ»
	moveYAngle = 0.0f;	//μ²Μpxϊ»
	moveXAngle = DX_PI_F;

	playerobj = MV1LoadModel("mv/p.x"); 
	skyobj = MV1LoadModel("mv/sora.mv1");
	kazi = NULL;
}

Player::~Player()
{
}

void Player::Updata(void)
{
	MoveControl();

	MV1SetPosition(playerobj, VGet(0.0f, -100.0f, 0.0f));	//ΜίΪ²ΤΐWΟX


	MV1SetPosition(playerobj, _pos);	//ΜίΪ²ΤΐWΟX
	MV1SetPosition(skyobj, _pos);	//ΜίΪ²ΤΐWΟX

	lpSceneMng.AddDrawQue(playerobj);	//ΜίΪ²Τ`ζv
	lpSceneMng.AddDrawQue(skyobj);	//`ζv
}

void Player::MoveControl(void)
{

	//μ
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

	tempCameraPos = _pos;	//μ²ΜΚuπΜίΪ²ΤΐWΕϊ»

	//μ²Μ³Μpxπίι
	tempf1 = static_cast<float>(sin(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = tempf1 * MOVE_DISTANCE;
	tempPos1.z = -tempf2 * MOVE_DISTANCE;

	//μ²Μ‘Μpxπίι
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
