#pragma once
#include "vector2.h"

// カメラの回転速度
#define LOOK_ANGLE_SPEED		0.5f

// カメラの高さ
#define CAMERA_HEIGHT		1000.0f

// カメラとﾌﾟﾚｲﾔ本体とのの距離
#define CAMERA_DISTANCE		1500.0f*3

class Camera
{
public:
	Camera();
	~Camera();
	void CameraRun(VECTOR targetPos);

private:
	void CameraInit(void);

	VECTOR	_Pos;
	float	cameraYAngle;			//カメラ横の角度
	float	cameraXAngle;			//カメラ縦の角度
	float	cameraDistance;			//カメラ距離


	Vector2 mouse;
};
