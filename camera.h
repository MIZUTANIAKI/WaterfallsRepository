#pragma once

// �J�����̉�]���x
#define LOOK_ANGLE_SPEED		0.5f

// �J�����̍���
#define CAMERA_HEIGHT		500.0f

// �J��������ڲԖ{�̂Ƃ̂̋���
#define CAMERA_DISTANCE		1200.0f

class Camera
{
public:
	Camera();
	~Camera();
	void CameraRun(VECTOR targetPos);

private:
	void CameraInit(void);

	VECTOR _Pos;
	float  cameraYAngle;			//�J�������̊p�x
	float  cameraXAngle;			//�J�����c�̊p�x
};

