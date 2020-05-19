#pragma once
#include <tuple>
#include <vector>
#include "obj.h"

#define S_GRAVITY -1.0f

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Run(void);

	void SetBullet(VECTOR pos,VECTOR vec);
private:
	VECTOR	_pos[2];
	VECTOR	_direction[2];	
	bool	_Shotflag;

	int		bulletobj;			//
	int		bulletmodel[2];
};

