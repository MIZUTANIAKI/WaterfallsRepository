#pragma once
#include "Obj.h"
#include "Bullet.h"


enum class STATE_ID			//敵の状態
{
	STAY,			//待機
	ACTIVE,			//目標に進む　攻撃を受けてなくても100000分の1の確率で、逃げ出す。
	ESCAPE,			//逃げる（なりふり構わず逃げ出し始める）　100000分の1の確率で、正気に戻る。 10秒後リセットされる。
	BREAK
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
		return unitID_;
	}
	VECTOR GetPos(void) override
	{
		return pos_;
	}

	void Updata(void) override;	//敵の更新用

	void Updata(VECTOR pos) override;	//敵の更新2プレイヤー情報取得用

private:
	STATE_ID state_;			//敵の状態
	
	int escCon_;

	int stayCon_;

	float hp_;
	bool drawF_;

	LORR LorR_;					//敵から見てプレイヤーはどっちにいるのか
	VECTOR ppos_;				//プレイヤー座標

	void	MoveControl(void);	//自機の移動処理

	float	moveYAngle_;			//操作軸の横の角度
	float	moveXAngle_;			//操作軸の横の角度
	VECTOR	movePos_;			//操作軸の位置

	//VECTOR	pos_;				//座標
	VECTOR	moveVec_;			//移動量保存

	bool	flag_;				//true＝帆を張るfalse＝帆をたたむ
	bool	fKeyold_;			//敵はたたまないようにしようかな
	int		flagcon_;			//旗のカウント

	int		oneCount_;			//一秒計測用

	//std::unique_ptr<Bullet>	nbullet1;			//敵の弾呼び出しよう

	static int econ_;

	int eID_;

	friend Bullet;

};

