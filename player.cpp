#include <DxLib.h>
#include "scene/SceneMng.h"
#include "player.h"

Player::Player()
{
	_pos = VGet(200.0f, -100.0f, 200.0f);	//��ڲԍ��W������

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

	MV1SetPosition(playerobj, VGet(0.0f, -100.0f, 0.0f));	//��ڲԍ��W�ύX


	MV1SetPosition(playerobj, _pos);	//��ڲԍ��W�ύX
	MV1SetPosition(skyobj, _pos);	//��ڲԍ��W�ύX


	lpSceneMng.AddDrawQue(playerobj);	//��ڲԕ`��v��
	lpSceneMng.AddDrawQue(skyobj);	//�`��v��
}

void Player::CameraControl(void)
{




	VECTOR tempPos1;
	VECTOR tempPos2;
	VECTOR tempCameraPos;
	float  tempf1;
	float  tempf2;

	tempCameraPos = _pos;	//�J�����̈ʒu����ڲԍ��W�ŏ�����
	tempCameraPos.y += CAMERA_HEIGHT;	//�����������ʒu�ɃJ�����̍��������Z

	//�J�����̍����̊p�x�����߂�
	tempf1 = static_cast<float>(sin(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(2.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = tempf1 * CAMERA_DISTANCE;
	tempPos1.z = -tempf2 * CAMERA_DISTANCE;

	//�J�����̉��̊p�x�����߂�
	tempf1 = static_cast<float>(sin(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(cameraYAngle / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = tempf2 * tempPos1.x - tempf1 * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = tempf1 * tempPos1.x + tempf2 * tempPos1.z;

	cameraPos = VAdd(tempPos2, tempCameraPos);	//���߂����W�ɏ��߂���ڲԍ��W�Őݒ肵���l�����Z���ăJ�������W�Ƃ���B


	SetCameraPositionAndTarget_UpVecY(cameraPos, tempCameraPos); 	//�J�����ʒu��ύX


}

void Player::cameraInit(void)
{
	cameraPos = VGet(0.0f, 5000.0f, 0.0f);	//�J�������W������
	cameraYAngle = 0.0f;	//�J�����p�x������
	cameraXAngle = DX_PI_F;
	SetCameraNearFar(100.0f, 100.0f);
}
