#include "obj.h"



Obj::Obj()
{
	_unitID = UNIT_ID::CPU;
	_pos = VGet(0.0f, 0.0f, 0.0f);	//ﾌﾟﾚｲﾔ座標初期化
}


Obj::~Obj()
{
}


