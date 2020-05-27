#pragma once
#include "vector2.h"

// �J�����̉�]���x
#define LOOK_ANGLE_SPEED		0.5f

// �J�����̍���
#define CAMERA_HEIGHT		1000.0f

// �J��������ڲԖ{�̂Ƃ̂̋���
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
	float	cameraYAngle;			//�J�������̊p�x
	float	cameraXAngle;			//�J�����c�̊p�x
	float	cameraDistance;			//�J��������


	Vector2 mouse;
};
