#pragma once
#include "obj.h"

// �ړ����x
#define MOVESPEED					10.0f

// ���쎲����ڲԖ{�̂Ƃ̂̋���
#define MOVE_DISTANCE		1200.0f

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

	float  moveYAngle;			//���쎲�̉��̊p�x
	float  moveXAngle;			//���쎲�̉��̊p�x
	VECTOR movePos;			//���쎲�̈ʒu
	
	VECTOR _pos;	//��ڲԍ��W
	VECTOR moveVec;	//��ڲԂ̈ړ��ʕۑ�
	int    playerobj;			//��ڲԃ��f���i�[�p
	int    skyobj;			//��
};
