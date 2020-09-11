#pragma once
#include "obj.h"
#include "Bullet.h"


/*	
	前回の二人での制作では、プレイヤーの後ろにカメラを置いて、カメラからプレイヤーをみて、移動方向を決めてるみたいだった。
	なので、必要のないと断言できた要素を取り外し、カメラと別々に動作させてみた。
*/

	

class Player :
	public Obj
{
public:
	Player();
	~Player();

	UNIT_ID GetUnitID(void) override
	{
		return unitID_;
	};

	VECTOR GetPos(void) override
	{
		return pos_;
	};

	void Updata(void) override;

	int GetSLR(void);

private:
	void MoveControl(void);	//ﾌﾟﾚｲﾔ移動処理
	int kazi_;				//舵を切る

	int shotLR_; //0==L 1==R
			
	float  moveYAngle_;			//操作軸の横の角度
	float  moveXAngle_;			//操作軸の横の角度
	VECTOR movePos_;				//操作軸の位置

	std::vector<int> pMcon_;
	std::vector<float> pMAng_;
	std::vector < std::pair<VECTOR, VECTOR> > pMmm_;
	
	int bcoon_;

	//VECTOR pos_;				//ﾌﾟﾚｲﾔ座標
	VECTOR tmppPos_;
	VECTOR moveVec_;				//ﾌﾟﾚｲﾔの移動量保存

	bool	flag_;				//true＝帆を張るfalse＝帆をたたむ
	bool	fKeyold_;			//Fが前のフレームに押されているか
	int		flagcon_;			//帆のカウント

	int		oneCount_;			//一秒計測用

	std::unique_ptr<Bullet> pbullet_;				//ﾌﾟﾚｲﾔ弾格納用

	friend Bullet;

	float bltAngl_;
};

