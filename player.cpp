#include <DxLib.h>
#include "scene/SceneMng.h"
#include "player.h"

Player::Player()
{
	_pos = VGet(200.0f, -100.0f, 200.0f);	//ﾌﾟﾚｲﾔ座標初期化

	moveVec = VGet(0.0f, 0.0f, 0.0f);
	playerobj = MV1LoadModel("mv/p.x"); 
	skyobj = MV1LoadModel("mv/sora.mv1");
	cameraInit();
}

Player::~Player()
{
}

void Player::Updata(void)
{

	CameraControl();

	VECTOR TempMoveVector;
	float  temp1;
	float  temp2;

	temp1 = static_cast<float>(sin(static_cast<double>(cameraYAngle / 180.0f)* DX_PI_F));
	temp2 = static_cast<float>(cos(static_cast<double>(cameraYAngle / 180.0f)* DX_PI_F));

	TempMoveVector.x = moveVec.x * temp2 - moveVec.z * temp1;

	TempMoveVector.y = moveVec.y;

	TempMoveVector.z = moveVec.x * temp1 + moveVec.z * temp2;

	moveVec = VGet(0.0f, 0.0f, 0.0f);

	_pos = VAdd(_pos, TempMoveVector);

	MV1SetPosition(playerobj, VGet(0.0f, -100.0f, 0.0f));	//ﾌﾟﾚｲﾔ座標変更


	MV1SetPosition(playerobj, _pos);	//ﾌﾟﾚｲﾔ座標変更
	MV1SetPosition(skyobj, _pos);	//ﾌﾟﾚｲﾔ座標変更


	lpSceneMng.AddDrawQue(playerobj);	//ﾌﾟﾚｲﾔ描画要求
	lpSceneMng.AddDrawQue(skyobj);	//描画要求
}

void Player::CameraControl(void)
{




	VECTOR tempPos1;
	VECTOR tempPos2;
	VECTOR tempCameraPos;
	float  tempf1;
	float  tempf2;

	tempCameraPos = _pos;	//カメラの位置をﾌﾟﾚｲﾔ座標で初期化
	tempCameraPos.y += CAMERA_HEIGHT;	//初期化した位置にカメラの高さを加算

	//カメラの高さの角度を求める
	tempf1 = static_cast<float>(sin(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = tempf1 * CAMERA_DISTANCE;
	tempPos1.z = -tempf2 * CAMERA_DISTANCE;

	//カメラの横の角度を求める
	tempf1 = static_cast<float>(sin(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = tempf2 * tempPos1.x - tempf1 * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = tempf1 * tempPos1.x + tempf2 * tempPos1.z;

	cameraPos = VAdd(tempPos2, tempCameraPos);	//求めた座標に初めにﾌﾟﾚｲﾔ座標で設定した値を加算してカメラ座標とする。


	SetCameraPositionAndTarget_UpVecY(cameraPos, tempCameraPos); 	//カメラ位置を変更


}

void Player::cameraInit(void)
{
	cameraPos = VGet(0.0f, 5000.0f, 0.0f);	//カメラ座標初期化
	cameraYAngle = 0.0f;	//カメラ角度初期化
	cameraXAngle = DX_PI_F;
	SetCameraNearFar(100.0f, 100.0f);
}
