#include "obj.h"

Obj::Obj()
{
	_unitID = UNIT_ID::NON;			//未設定に
	_pos = VGet(0.0f, 0.0f, 0.0f);	//座標初期化
}


Obj::~Obj()
{
}


