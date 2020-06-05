#pragma once
#include "obj.h"
#include "Bullet.h"

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

	UNIT_ID GetUnitID(void) override
	{
		return _unitID;
	};

	VECTOR GetPos(void) override
	{
		return _pos;
	};

	void Updata(void) override;

private:
	void MoveControl(void);	//��ڲԈړ�����
	int kazi;				//�ǂ�؂�
			
	float  moveYAngle;			//���쎲�̉��̊p�x
	float  moveXAngle;			//���쎲�̉��̊p�x
	VECTOR movePos;				//���쎲�̈ʒu
	
	//VECTOR _pos;				//��ڲԍ��W
	VECTOR _tmppPos;
	VECTOR moveVec;				//��ڲԂ̈ړ��ʕۑ�

	bool	_flag;				//true�����𒣂�false������������
	bool	fKeyold;			//F���O�̃t���[���ɉ�����Ă��邩
	int		_flagcon;			//���̃J�E���g

	int		oneCount;			//��b�v���p

	Bullet pbullet;				//��ڲԒe�i�[�p
};
