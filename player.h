#pragma once
#include "obj.h"

// 移動速度
#define MOVESPEED					10.0f

// カメラとﾌﾟﾚｲﾔ本体とのの距離
#define CAMERA_DISTANCE		1200.0f

// カメラの高さ
#define CAMERA_HEIGHT		350.0f

#define MAX_CAMERA_FAR  7000.0f

// 角度変化速度
#define PLAYER_ANGLE_SPEED			0.2f		

class Player :
	public Obj
{
public:
	Player();
	~Player();
	void Updata(void);

private:
	void MoveControl(void);	//自機の移動処理
	int kazi;


	void cameraInit(void);
	float  moveYAngle;			//横の角度
	float  moveXAngle;			//横の角度
	VECTOR movePos;			//操作軸の位置
	VECTOR moveTarget;		//操作軸の注視点

	VECTOR _pos;	//ﾌﾟﾚｲﾔ座標
	VECTOR moveVec;	//ﾌﾟﾚｲﾔの移動量保存
	int    playerobj;			//ﾌﾟﾚｲﾔモデル格納用
	int    skyobj;			//空
};
