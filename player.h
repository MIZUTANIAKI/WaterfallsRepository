#pragma once
#include "obj.h"

// ˆÚ“®‘¬“x
#define MOVESPEED					10.0f

class Player :
	public Obj
{
public:
	Player();
	~Player();
	void Updata(void);
private:
	VECTOR _pos;
	int    playerobj;			//ÌßÚ²Ôƒ‚ƒfƒ‹Ši”[—p
};

