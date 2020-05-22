#pragma once
#include "Obj.h"
#include "Bullet.h"

// 移動速度
#define MOVESPEED					10.0f

// 操作軸の自分とのの距離
#define MOVE_DISTANCE		1200.0f

// 角度変化速度
#define PLAYER_ANGLE_SPEED			0.2f		

enum class STATE_ID			//それぞれの立場
{
	STAY,
	ACTIVE,
	ESCAPE
};

enum class LORR
{
	LEFT,
	RIGHT,
	NON
};

class Enemy :
	public Obj
{
public:

	Enemy();
	~Enemy();

	UNIT_ID GetUnitID(void) override
	{
		return _unitID;
	}
	VECTOR GetPos(void) override
	{
		return _pos;
	}

	void Updata(void) override;

	void Updata(VECTOR pos) override;

private:
	STATE_ID _State;

	LORR _LorR;
	VECTOR _ppos;
	VECTOR _direction;

	void	MoveControl(void);	//自機の移動処理

	float	moveYAngle;			//操作軸の横の角度
	float	moveXAngle;			//操作軸の横の角度
	VECTOR	movePos;			//操作軸の位置

	VECTOR	_pos;				//座標
	VECTOR	moveVec;			//移動量保存
	int		enemyobj;			//敵モデル格納用

	bool	_flag;				//true＝帆を張るfalse＝帆をたたむ
	bool	fKeyold;
	int		_flagcon;

	int		oneCount;

	Bullet	nbullet1;

};

