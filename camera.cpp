#include <math.h>
#include <DxLib.h>
#include "camera.h"

Camera::Camera()
{
	CameraInit();
}

Camera::~Camera()
{
}

void Camera::CameraInit(void)
{
	// カメラの座標を初期化
	_Pos.x = 0.0f;
	_Pos.y = 500.0f;
	_Pos.z = 800.0f;
	cameraYAngle = 0.0f;
	cameraXAngle = 2.0f;
}

void Camera::CameraRun(VECTOR targetPos)
{
	if (CheckHitKey(KEY_INPUT_A))
	{
		cameraYAngle += LOOK_ANGLE_SPEED;
		if (cameraYAngle >= 180.0f)
		{
			cameraYAngle -= 360.0f;
		}
	}

	else if (CheckHitKey(KEY_INPUT_D))
	{
		cameraYAngle -= LOOK_ANGLE_SPEED;
		if (cameraYAngle <= -180.0f)
		{
			cameraYAngle += 360.0f;
		}
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		cameraXAngle += LOOK_ANGLE_SPEED;
		if (cameraXAngle >= 180.0f)
		{
			cameraXAngle -= 360.0f;
		}
	}

	else if (CheckHitKey(KEY_INPUT_S))
	{
		cameraXAngle -= LOOK_ANGLE_SPEED;
		if (cameraXAngle <= -180.0f)
		{
			cameraXAngle += 360.0f;
		}
	}

	VECTOR tempPos1= VGet(0.0f, 0.0f, 0.0f);
	VECTOR tempPos2= VGet(0.0f, 0.0f, 0.0f);
	VECTOR tempCameraPos= VGet(0.0f, 0.0f, 0.0f);
	float pSin=NULL, pCos=NULL;

	tempCameraPos = targetPos;	//カメラの位置をﾌﾟﾚｲﾔ座標で初期化
	tempCameraPos.y += CAMERA_HEIGHT;	//初期化した位置にカメラの高さを加算

	//カメラの高さの角度を求める
	pSin = static_cast<float>(sin(cameraXAngle / 180.0f * static_cast<double>(DX_PI_F)));
	pCos = static_cast<float>(cos(cameraXAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = pSin * CAMERA_DISTANCE;
	tempPos1.z = -pCos * CAMERA_DISTANCE;

	//カメラの横の角度を求める
	pSin = static_cast<float>(sin(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	pCos = static_cast<float>(cos(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = pCos * tempPos1.x - pSin * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = pSin * tempPos1.x + pCos * tempPos1.z;

	VECTOR temptempCameraPos= VGet(0.0f, 0.0f, 0.0f);
	temptempCameraPos = VAdd(tempPos2, tempCameraPos);	//求めた座標に初めにﾌﾟﾚｲﾔ座標で設定した値を加算してカメラ座標とする。

	SetCameraPositionAndTarget_UpVecY(temptempCameraPos, targetPos);
}

