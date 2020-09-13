#include <math.h>
#include "Dxlib.h"
#include "scene/SceneMng.h"
#include "Scene/GameScene.h"
#include "Bullet.h"
#include "enemy.h"
#include "objmnj.h"

int Enemy::econ_ = 0;

Enemy::Enemy()
{
	unitID_ = UNIT_ID::CPU;
	eID_ = econ_;
	if (eID_ == 0)
	{
		pos_ = VGet(2000.0f, 0.0f, 5000.0f);	//敵の座標初期化
	}
	else if (eID_ == 1)
	{
		pos_ = VGet(2000.0f, 0.0f, 6000.0f);	//敵の座標初期化
	}
	else if (eID_ == 2)
	{
		pos_ = VGet(2000.0f, 0.0f, 7000.0f);	//敵の座標初期化
	}
	else
	{
		pos_ = VGet(rand() % 10000 - 5000.0f, 0.0f, 10000.0f);
	}
	moveVec_ = VGet(0.0f, 0.0f, -1.0f);
	movePos_ = VGet(0.0f, 5000.0f, 0.0f);	//操作軸の座標初期化
	moveYAngle_ = 180.0f;	//操作軸の角度初期化
	moveXAngle_ = DX_PI_F;

	flag_ = true;
	flagcon_ = 10;
	fKeyold_ = false;
	oneCount_ = GetNowCount();
	ppos_ = VGet(0.0f, 0.0f, 0.0f);
	state_ = STATE_ID::ACTIVE;
	LorR_ = LORR::NON;

	//nbullet1.reset(new Bullet(UNIT_ID::PLAYER));
	econ_++;
	hp_ = 25;
	drawF_ = true;
	stayCon_ = 0;
	escCon_ = 0;
}

Enemy::~Enemy()
{
	econ_ = 0;
}

void Enemy::Updata(void)
{	
	bool resetF = false;

	if (state_ == STATE_ID::STAY)
	{
		if (stayCon_ / 10 % 2 == 0)
		{
			resetF = true;
		}
	}
	if (!resetF)
	{
		//向きを変更	
		lpobjlMng.ObjRotation(unitID_, -moveYAngle_, eID_);
		//座標設定		
		lpobjlMng.Setobjpos(pos_, moveVec_, unitID_, eID_);
		//描画に投げる	
		lpobjlMng.ObjDraw(unitID_, eID_);
	}

	resetF =false;

	if (drawF_ == false)
	{
		pos_.y -= 3;
		if (pos_.y < -1000)
		{
			resetF = true;
		}
	}
	if (state_ == STATE_ID::ESCAPE)
	{
		if (escCon_ / 60 >= 10)
		{
			resetF = true;
		}
		escCon_++;
	}
	if (pos_.z < -5000)
	{
		resetF = true;
	}
	if (resetF)
	{
		stayCon_ = 0;
		escCon_ = 0;
		hp_ = 25;
		drawF_ = true;
		pos_ = VGet(rand() % 10000 - 5000.0f, 0.0f, 10000.0f);	//敵の座標初期化
		state_ = STATE_ID::STAY;

		moveVec_ = VGet(0.0f, 0.0f, -1.0f);
		movePos_ = VGet(0.0f, 5000.0f, 0.0f);	//操作軸の座標初期化
		moveYAngle_ = 180.0f;	//操作軸の角度初期化
	}
}

void Enemy::Updata(VECTOR pos)
{

	//if(abs(VSub(pos_, pos).z)<3000.0f&& abs(VSub(pos_, pos).x) < 3000.0f)
	//{
	//	state_ = STATE_ID::ACTIVE;
	//}
	//else
	//{
	//	state_ = STATE_ID::STAY;
	//}
	if (state_ == STATE_ID::STAY)
	{
		if (stayCon_ / 60 >= 3)
		{
			state_ = STATE_ID::ACTIVE;
		}
		else
		{
			stayCon_++;
		}
	}
	else if (state_ == STATE_ID::ACTIVE)
	{
		ppos_ = pos;
		if (CheckHitKey(KEY_INPUT_F))
		{
			if (!fKeyold_)
			{
				if (!flag_)
				{
					flag_ = true;
				}
				else
				{
					flag_ = false;
					flagcon_ = 10;
				}
			}
		}

		if (moveVec_.z > -1.0f)
		{
			moveVec_.z--;
		}
		else if (moveVec_.z < -1.0f)
		{
			moveVec_.z++;
		}
		// １秒たっているか
		if (GetNowCount() - oneCount_ > 1000)
		{
			if (!flag_)
			{
				flagcon_--;
				oneCount_ = GetNowCount();
			}
			if (rand() % 100000 == 0)
			{
				//100000分の1の確率で、逃げ出す。
				state_ = STATE_ID::ESCAPE;
			}
		}

		if (lpobjlMng.ObjCollHit(pos_, unitID_))
		{
			if (rand() % 50 == 0)
			{
				state_ = STATE_ID::ESCAPE;
			}
			escCon_ = 0;
			hp_ -= rand() % 3+1;
		}
		if (hp_ <= 0)
		{
			state_ = STATE_ID::BREAK;
			drawF_ = false;
		}
		MoveControl();

		//nbullet1->Run();
	}
	else if (state_ == STATE_ID::ESCAPE)
	{
		ppos_ = pos;

		// １秒たっているか
		if (GetNowCount() - oneCount_ > 1000)
		{
			if (rand() % 100000 == 0)
			{
				//100000分の1の確率で、作戦に戻る。
				escCon_ = 0;
				state_ = STATE_ID::ACTIVE;
			}
		}

		if (lpobjlMng.ObjCollHit(pos_, unitID_))
		{
			hp_-=5;
		}
		if (hp_ <= 0)
		{
			state_ = STATE_ID::BREAK;
			drawF_ = false;
		}

		MoveControl();

		//nbullet1->Run();
	}
}

void Enemy::MoveControl(void)
{
	if(state_ == STATE_ID::STAY)
	{
	}
	else if(state_ == STATE_ID::ACTIVE)
	{
	}
	else if(state_ == STATE_ID::ESCAPE)
	{

		VECTOR tmpcrossvec = VCross(VSub(pos_, movePos_), VSub(pos_, ppos_));
		if (tmpcrossvec.x == 0.0f && tmpcrossvec.z == 0.0f)
		{
			LorR_ = LORR::NON;
		}
		if (!signbit(tmpcrossvec.x))
		{
			//プラスの場合は、右に
			LorR_ = LORR::RIGHT;
			moveYAngle_ += 0.1f;
			if (moveYAngle_ >= 180.0f)
			{
				moveYAngle_ -= 360.0f;
			}
		}

		if(!signbit(tmpcrossvec.z))
		{
			//プラスの場合は、右に
			LorR_ = LORR::RIGHT;
			moveYAngle_ += 0.1f;
			if (moveYAngle_ >= 180.0f)
			{
				moveYAngle_ -= 360.0f;
			}
		}
		
		if (signbit(tmpcrossvec.x))
		{
			//マイナスの場合は左に
			LorR_ = LORR::LEFT;
			moveYAngle_ -= 0.1f;
			if (moveYAngle_ <= -180.0f)
			{
				moveYAngle_ += 360.0f;
			}
		}
		if(signbit(tmpcrossvec.z))
		{
			//マイナスの場合は左に
			LorR_ = LORR::LEFT;
			moveYAngle_ -= 0.1f;
			if (moveYAngle_ <= -180.0f)
			{
				moveYAngle_ += 360.0f;
			}
		}
		
		/*if (LorR_ == LORR::RIGHT)
		{
			moveYAngle_ += 0.1f;
			if (moveYAngle_ >= 180.0f)
			{
				moveYAngle_ -= 360.0f;
			}

		}
		else if(LorR_ == LORR::LEFT)
		{
			moveYAngle_ -= 0.1f;
			if (moveYAngle_ <= -180.0f)
			{
				moveYAngle_ += 360.0f;
			}

		}
		else
		{

		}*/
	
	}
	
	//if ( pos_.x > ppos_.x/*&&  pos_.z > ppos_.z*/)
	//{
	//}

	if (flag_)
	{
		moveVec_.z += 3.0f;
	}
	else
	{
		if (flagcon_ >= 8)
		{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
			moveVec_.z += 4.0f;
		}
		else if (flagcon_ >= 6)
		{
			moveVec_.z += 3.0f;
		}
		else if (flagcon_ >= 4)
		{
			moveVec_.z += 2.0f;
		}
		else
		{
			moveVec_.z += 1.0f;
		}
	}

	//lpobjlMng.ObjCollHit(pos_, &moveVec_, unitID_);
	VECTOR tempPos1;
	VECTOR tempPos2;
	VECTOR tempMovePos;
	VECTOR tempMoveVec;
	float  tempf1;
	float  tempf2;
	float  temp1;
	float  temp2;

	//if (!lpobjlMng.ObjCollHit(pos_, &moveVec_, unitID_))
	//{
	//	moveVec_ = VGet(-moveVec_.x, 0, -moveVec_.z);
	//}

	tempMovePos = pos_;	//操作軸の位置をﾌﾟﾚｲﾔ座標で初期化

	//操作軸の高さの角度を求める
	tempf1 = static_cast<float>(sin(1.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(1.0f / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos1.x = 0.0f;
	tempPos1.y = 0.0f;
	tempPos1.z = -tempf2 * MOVE_DISTANCE;

	//操作軸の横の角度を求める
	tempf1 = static_cast<float>(sin(moveYAngle_ / 180.0f * static_cast<double>(DX_PI_F)));
	tempf2 = static_cast<float>(cos(moveYAngle_ / 180.0f * static_cast<double>(DX_PI_F)));
	tempPos2.x = tempf2 * tempPos1.x - tempf1 * tempPos1.z;
	tempPos2.y = tempPos1.y;
	tempPos2.z = tempf1 * tempPos1.x + tempf2 * tempPos1.z;

	movePos_ = VAdd(tempPos2, tempMovePos);

	temp1 = static_cast<float>(sin(static_cast<double>(moveYAngle_ / 180.0f)* DX_PI_F));
	temp2 = static_cast<float>(cos(static_cast<double>(moveYAngle_ / 180.0f)* DX_PI_F));

	tempMoveVec.x = moveVec_.x * temp2 - moveVec_.z * temp1;
	tempMoveVec.y = 0.0f;
	tempMoveVec.z = moveVec_.x * temp1 + moveVec_.z * temp2;
	moveVec_ = tempMoveVec;
	pos_ = VAdd(pos_, moveVec_);/*
	pos_ = VAdd(pos_, tempMoveVec);*/
	moveVec_ = VGet(0.0f, 0.0f, 0.0f);

	float tmptmpfl = ((pos_.x - pos_.x)*(pos_.x - pos_.x)+((pos_.z - pos_.z)*(pos_.z - pos_.z)));


	if (state_ == STATE_ID::ACTIVE && sqrt(tmptmpfl) < 5000.0f)/*(abs(VSub(ppos_,pos_ ).x) < 1000.0f&& abs(VSub(ppos_, pos_).z) < 1000.0f)*/
	{
		VECTOR tmpvec1 = pos_, tmpvec2 = movePos_;

		tmpvec1.y = 0.0f;
		tmpvec2.y = 0.0f;

		VECTOR tmpcrossvec = VCross(VSub(pos_, movePos_), VSub(pos_, ppos_));
		int LorR_ = 0;
		if (tmpcrossvec.x == 0.0f && tmpcrossvec.z == 0.0f)
		{
			LorR_ = -1;
		}
		if (!signbit(tmpcrossvec.x))
		{
			//プラスの場合は、右に
			LorR_ = 0;
		}

		if (!signbit(tmpcrossvec.z))
		{
			//プラスの場合は、右に
			LorR_ = 0;
		}

		if (signbit(tmpcrossvec.x))
		{
			//マイナスの場合は左に
			LorR_ = 1;
		}
		if (signbit(tmpcrossvec.z))
		{
			//マイナスの場合は左に
			LorR_ = 1;
		}

		if (LorR_ != -1)
		{
			//nbullet1->SetBullet(VAdd(pos_, VGet(0.0f, 100.0f, 0.0f)), VNorm(VSub(tmpvec1, tmpvec2)), eID_, LorR_);
		}
	}
}

