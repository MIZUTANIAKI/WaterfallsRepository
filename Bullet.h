#pragma once
#include <tuple>
#include <vector>
#include "obj.h"

#define S_GRAVITY -9.8/60 //重力加速度

#define BULLETMAX 4


class Bullet
{
public:
	Bullet();
	~Bullet();

	void Run(void);

	void SetBullet(VECTOR pos,VECTOR vec);
private:
	VECTOR	_pos[BULLETMAX];		//弾の座標
	VECTOR	_direction[BULLETMAX];	//弾の向き
	bool	_Shotflag[BULLETMAX];	//弾のフラグ

	int		_bulletCon[BULLETMAX];	//弾の装填に使用する予定ですが、プレイヤーと、エネミーに変数を持たせるか考え中
};

