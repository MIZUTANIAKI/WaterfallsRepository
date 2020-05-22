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
	STAY,
	ACTIVE,
	ESCAPE
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

	void Updata(void) override;

	void Updata(VECTOR pos) override;

private:
	STATE_ID _State;

	LORR _LorR;
	VECTOR _ppos;
	VECTOR _direction;

	void	MoveControl(void);	//���@�̈ړ�����

	float	moveYAngle;			//���쎲�̉��̊p�x
	float	moveXAngle;			//���쎲�̉��̊p�x
	VECTOR	movePos;			//���쎲�̈ʒu

	VECTOR	_pos;				//���W
	VECTOR	moveVec;			//�ړ��ʕۑ�
	int		enemyobj;			//�G���f���i�[�p

	bool	_flag;				//true�����𒣂�false������������
	bool	fKeyold;
	int		_flagcon;

	int		oneCount;

	Bullet	nbullet1;

};

