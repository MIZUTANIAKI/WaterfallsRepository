#include <math.h>
#include <DxLib.h>
#include "camera.h"
#include "Scene/sceneMng.h"

Camera::Camera()
{
	CameraInit();
	
	SetMousePoint(lpSceneMng.ScreenSize.x/2, lpSceneMng.ScreenSize.y/2);
}

Camera::~Camera()
{
}

void Camera::CameraInit(void)
{
	// �J�����̍��W��������
	_Pos.x = 0.0f;
	_Pos.y = 1000.0f;
	_Pos.z = 800.0f;
	cameraYAngle = 0.0f;
	cameraXAngle = 2.0f;
	mouse.x = 0;
	mouse.y = 0;
	cameraDistance = CAMERA_DISTANCE;
}


void Camera::CameraRun(VECTOR targetPos)
{

	GetMousePoint(&mouse.x, &mouse.y);


	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
	{
		// �z�C�[���I��
		SetMousePoint(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2);
		cameraDistance = CAMERA_DISTANCE;
	}
	else
	{	
		cameraDistance -= static_cast<float>(GetMouseWheelRotVol()*50);

		if (cameraDistance < 400)
		{
			cameraDistance = 400;
		}
		if (cameraDistance > CAMERA_DISTANCE*3)
		{
			cameraDistance = CAMERA_DISTANCE*3;
		}

		// �z�C�[���I�t
		if (lpSceneMng.ScreenSize.x / 2 - 100 >= mouse.x)	//CheckHitKey(KEY_INPUT_A)
		{
			mouse.x = lpSceneMng.ScreenSize.x / 2 - 100;
			cameraYAngle -= LOOK_ANGLE_SPEED;
			if (cameraYAngle >= 180.0f)
			{
				cameraYAngle -= 360.0f;
			}

		}

		if (lpSceneMng.ScreenSize.x / 2 + 100 <= mouse.x)
		{
			mouse.x = lpSceneMng.ScreenSize.x / 2 + 100;

			cameraYAngle += LOOK_ANGLE_SPEED;
			if (cameraYAngle <= -180.0f)
			{
				cameraYAngle += 360.0f;
			}
		}

		if (lpSceneMng.ScreenSize.y / 2 - 100 >= mouse.y)
		{
			mouse.y = lpSceneMng.ScreenSize.y / 2 - 100;

			cameraXAngle += LOOK_ANGLE_SPEED;
			if (cameraXAngle <= -180.0f)
			{
				cameraXAngle += 360.0f;
			}
		}

		if (lpSceneMng.ScreenSize.y / 2 + 100 <= mouse.y)
		{
			mouse.y = lpSceneMng.ScreenSize.y / 2 + 100;

			cameraXAngle -= LOOK_ANGLE_SPEED;
			if (cameraXAngle >= 180.0f)
			{
				cameraXAngle -= 360.0f;
			}

		}

		if (cameraXAngle < -5.0f)
		{
			cameraXAngle = -5.0f;
		}
		if (cameraXAngle > 20.0f)
		{
			cameraXAngle = 20.0f;
		}

		SetMousePoint(mouse.x, mouse.y);

	}




	VECTOR tempPos1= VGet(0.0f, 0.0f, 0.0f);
	VECTOR tempPos2= VGet(0.0f, 0.0f, 0.0f);
	VECTOR tempCameraPos= VGet(0.0f, 0.0f, 0.0f);
	float pSin=NULL, pCos=NULL;

	tempCameraPos = VAdd(targetPos,VGet(0.0f,100.0f,0.0f));	//�J�����̈ʒu����ڲԍ��W�ŏ�����
	tempCameraPos.y += CAMERA_HEIGHT;	//�����������ʒu�ɃJ�����̍��������Z

	//�J�����̍����̊p�x�����߂�
	pSin = static_cast<float>(sin(cameraXAngle / 180.0f * static_cast<double>(DX_PI_F)));
	pCos = static_cast<float>(cos(cameraXAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = pSin * cameraDistance;
	tempPos1.z = -pCos * cameraDistance;

	//�J�����̉��̊p�x�����߂�
	pSin = static_cast<float>(sin(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	pCos = static_cast<float>(cos(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = pCos * tempPos1.x - pSin * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = pSin * tempPos1.x + pCos * tempPos1.z;

	VECTOR temptempCameraPos= VGet(0.0f, 0.0f, 0.0f);
	temptempCameraPos = VAdd(tempPos2, tempCameraPos);	//���߂����W�ɏ��߂���ڲԍ��W�Őݒ肵���l�����Z���ăJ�������W�Ƃ���B

	SetCameraPositionAndTarget_UpVecY(temptempCameraPos, VAdd(targetPos,VGet(0.0f,1000.0f,0.0f)));
}

