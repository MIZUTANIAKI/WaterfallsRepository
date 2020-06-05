#pragma once
#include <tuple>
#include <vector>
#include "obj.h"

#define S_GRAVITY -9.8/60 //�d�͉����x

#define BULLETMAX 4


class Bullet
{
public:
	Bullet();
	~Bullet();

	void Run(void);

	void SetBullet(VECTOR pos,VECTOR vec);
private:
	VECTOR	_pos[BULLETMAX];		//�e�̍��W
	VECTOR	_direction[BULLETMAX];	//�e�̌���
	bool	_Shotflag[BULLETMAX];	//�e�̃t���O

	int		_bulletCon[BULLETMAX];	//�e�̑��U�Ɏg�p����\��ł����A�v���C���[�ƁA�G�l�~�[�ɕϐ����������邩�l����
};

