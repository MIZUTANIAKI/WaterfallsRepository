#include "obj.h"

Obj::Obj()
{
	unitID_ = UNIT_ID::CPU;
	pos_ = VGet(0.0f, 0.0f, 0.0f);	//ﾌﾟﾚｲﾔ座標初期化
}


Obj::~Obj()
{
}


