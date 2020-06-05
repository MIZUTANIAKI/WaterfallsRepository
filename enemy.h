#pragma once
#include "Obj.h"
#include "Bullet.h"

// �ړ����x
#define MOVESPEED					10.0f

// ���쎲�̎����Ƃ̂̋���
#define MOVE_DISTANCE		1200.0f

// �p�x�ω����x
#define PLAYER_ANGLE_SPEED			0.2f		

enum class STATE_ID			//���ꂼ��̗���
{
	STAY,			//�ҋ@
	ACTIVE,			//�ڕW�ɐi��
	ESCAPE			//������
};	

enum class LORR
{
	LEFT,
	RIGHT,
	NON
};

class Enemy :
	public Obj
{
public:

	Enemy();
	~Enemy();

	UNIT_ID GetUnitID(void) override
	{
		return _unitID;
	}
	VECTOR GetPos(void) override
	{
		return _pos;
	}

	void Updata(void) override;	//�G�̍X�V�p

	void Updata(VECTOR pos) override;	//�G�̍X�V2�v���C���[���擾�p

private:
	STATE_ID _State;			//�G�̏��

	LORR _LorR;					//�G���猩�ăv���C���[�͂ǂ����ɂ���̂�
	VECTOR _ppos;				//�v���C���[���W

	void	MoveControl(void);	//���@�̈ړ�����

	float	moveYAngle;			//���쎲�̉��̊p�x
	float	moveXAngle;			//���쎲�̉��̊p�x
	VECTOR	movePos;			//���쎲�̈ʒu

	//VECTOR	_pos;				//���W
	VECTOR	moveVec;			//�ړ��ʕۑ�

	bool	_flag;				//true�����𒣂�false������������
	bool	fKeyold;			//�G�͂����܂Ȃ��悤�ɂ��悤����
	int		_flagcon;			//���̃J�E���g

	int		oneCount;			//��b�v���p

	Bullet	nbullet1;			//�G�̒e�Ăяo���悤

};

