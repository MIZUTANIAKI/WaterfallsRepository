#pragma once
#include <tuple>
#include <vector>
#include "obj.h"

#define S_GRAVITY -9.8/60 //�d�͉����x

#define BULLETMAX 3


class Bullet
{
public:
	Bullet(UNIT_ID id);
	~Bullet();

	void Run(void);

	void SetBullet(VECTOR pos,VECTOR vec,int non,int pnum);
private:
	std::vector<VECTOR>	pos_;		//�e�̍��W
	std::vector<VECTOR>	direction_;	//�e�̌���
	std::vector<bool>	shotflag_;	//�e�̃t���O
	std::vector<int>	bulletCon_;

	UNIT_ID BuniD_;
	int bcon_;
};

