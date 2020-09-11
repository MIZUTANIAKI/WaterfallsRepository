#pragma once
#include <tuple>
#include <vector>
#include "obj.h"

#define S_GRAVITY -9.8/60 //重力加速度

#define BULLETMAX 3


class Bullet
{
public:
	Bullet(UNIT_ID id);
	~Bullet();

	void Run(void);

	void SetBullet(VECTOR pos,VECTOR vec,int non,int pnum);
private:
	std::vector<VECTOR>	pos_;		//弾の座標
	std::vector<VECTOR>	direction_;	//弾の向き
	std::vector<bool>	shotflag_;	//弾のフラグ
	std::vector<int>	bulletCon_;

	UNIT_ID BuniD_;
	int bcon_;
};

