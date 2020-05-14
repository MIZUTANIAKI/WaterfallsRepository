#pragma once
#include "obj.h"

// �ړ����x
#define MOVESPEED					10.0f

// �J��������ڲԖ{�̂Ƃ̂̋���
#define CAMERA_DISTANCE		1200.0f

// �J�����̍���
#define CAMERA_HEIGHT		350.0f

#define MAX_CAMERA_FAR  7000.0f

// �p�x�ω����x
#define PLAYER_ANGLE_SPEED			0.2f		

class Player :
	public Obj
{
public:
	Player();
	~Player();
	void Updata(void);

private:
	void MoveControl(void);	//���@�̈ړ�����
	int kazi;


	void cameraInit(void);
	float  moveYAngle;			//���̊p�x
	float  moveXAngle;			//���̊p�x
	VECTOR movePos;			//���쎲�̈ʒu
	VECTOR moveTarget;		//���쎲�̒����_

	VECTOR _pos;	//��ڲԍ��W
	VECTOR moveVec;	//��ڲԂ̈ړ��ʕۑ�
	int    playerobj;			//��ڲԃ��f���i�[�p
	int    skyobj;			//��
};
