#pragma once
#include "obj.h"
#include "Bullet.h"

// 移動速度
#define MOVESPEED					10.0f

// 操作軸のﾌﾟﾚｲﾔ本体とのの距離
#define MOVE_DISTANCE		1200.0f

// 角度変化速度
#define PLAYER_ANGLE_SPEED			0.2f		

class Player :
	public Obj
{
public:
	Player();
	~Player();

	UNIT_ID GetUnitID(void) override
	{
		return _unitID;
	};

	VECTOR GetPos(void) override
	{
		return _pos;
	};

	void Updata(void);

private:
	void MoveControl(void);	//自機の移動処理
	int kazi;

	float  moveYAngle;			//操作軸の横の角度
	float  moveXAngle;			//操作軸の横の角度
	VECTOR movePos;				//操作軸の位置
	
	VECTOR _pos;				//ﾌﾟﾚｲﾔ座標
	VECTOR moveVec;				//ﾌﾟﾚｲﾔの移動量保存
	int    playerobj;			//ﾌﾟﾚｲﾔモデル格納用
	int    skyobj;				//空

	bool	_flag;				//true＝帆を張るfalse＝帆をたたむ
	bool	fKeyold;
	int		_flagcon;

	int		oneCount;

	Bullet pbullet1;
};
