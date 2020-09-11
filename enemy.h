#pragma once
#include "Obj.h"
#include "Bullet.h"

	

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
		return unitID_;
	}
	VECTOR GetPos(void) override
	{
		return pos_;
	}

	void Updata(void) override;	//�G�̍X�V�p

	void Updata(VECTOR pos) override;	//�G�̍X�V2�v���C���[���擾�p

private:
	STATE_ID state_;			//�G�̏��

	int hp_;
	bool drawF_;

	LORR LorR_;					//�G���猩�ăv���C���[�͂ǂ����ɂ���̂�
	VECTOR ppos_;				//�v���C���[���W

	void	MoveControl(void);	//���@�̈ړ�����

	float	moveYAngle_;			//���쎲�̉��̊p�x
	float	moveXAngle_;			//���쎲�̉��̊p�x
	VECTOR	movePos_;			//���쎲�̈ʒu

	//VECTOR	pos_;				//���W
	VECTOR	moveVec_;			//�ړ��ʕۑ�

	bool	flag_;				//true�����𒣂�false������������
	bool	fKeyold_;			//�G�͂����܂Ȃ��悤�ɂ��悤����
	int		flagcon_;			//���̃J�E���g

	int		oneCount_;			//��b�v���p

	std::unique_ptr<Bullet>	nbullet1;			//�G�̒e�Ăяo���悤

	static int econ_;

	int eID_;

	friend Bullet;

};

