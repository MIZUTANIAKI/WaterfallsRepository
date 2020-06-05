#pragma once
#include "Dxlib.h"
#include<memory>

enum class UNIT_ID			//それぞれの立場
{
	PLAYER,	//プレイヤーキャラ
	CPU,	//プレイヤー操作じゃないキャラ
	BULLET,	//弾
	NON,	//未割当
	MAX,	
};


class Obj;

using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	~Obj();
	virtual UNIT_ID GetUnitID(void)	//ユニットIDを返す
	{
		return _unitID;
	}
	virtual VECTOR GetPos(void)	//位置情報を返す
	{
		return _pos;
	}

	virtual void Updata(void) = 0;	//OBJ系の更新用

	virtual void Updata(VECTOR pos)	//OBJ系の更新用2ほかのOBJ系の座標などがいる場合
	{
		return;
	}

	void SetUnitID(UNIT_ID unitID) { _unitID = unitID; }
protected:
	VECTOR _pos;	//座標格納
	UNIT_ID _unitID;	//ユニットID格納
};

