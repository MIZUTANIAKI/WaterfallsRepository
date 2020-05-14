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
	void CameraControl(void);	//カメラ操作処理
	int kazi;


	void cameraInit(void);
	float  cameraYAngle;			//カメラ横の角度
	float  cameraXAngle;			//カメラ横の角度
	VECTOR cameraPos;			//カメラの位置
	VECTOR cameraTarget;		//カメラの注視点

	VECTOR _pos;	//ﾌﾟﾚｲﾔ座標
	VECTOR moveVec;	//ﾌﾟﾚｲﾔの移動量保存
	int    playerobj;			//ﾌﾟﾚｲﾔモデル格納用
	int    skyobj;			//空
};
