#include <iostream>
#include <DxLib.h>
#include "Scene/sceneMng.h"
#include "Bullet.h"
#include "objmnj.h"
#include "SoundMnj.h"

//斜め下に打つのではなく、楕円描きながら落としたい
//水平に、等速直線運動して、下向きに自由落下している状態らしい
//等速は、速度が、一定のまま進んでいく。
//自由落下、重力加速度は9.8[m/s²]で固定。
//つまり初速*時間+(重力加速度*時間)/2？

Bullet::Bullet(UNIT_ID id)
{
	BuniD_ = id;
	for (int i = 0; i < BULLETMAX; i++)
	{
		shotflag_.emplace_back(false);
		bulletCon_.emplace_back(0);
		pos_.emplace_back(VGet(0.0f, 0.0f, 0.0f));
		direction_.emplace_back(VGet(0.0f, 0.0f, 0.0f));
	}
	bcon_ = 0;
}

Bullet::~Bullet()
{
}

void Bullet::Run(void)
{
	//if (lpSceneMng.GetFcon() % 5 == 0)
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (shotflag_[i] == true)
			{
				lpSceneMng.SetEffect(EffectName::testef, pos_[i]);

				VECTOR tmpvec, tmpmove;
				tmpmove.x = direction_[i].x;
				tmpmove.z = direction_[i].z;
				tmpmove.y = 0.0f;
				tmpvec = VAdd(pos_[i], tmpmove);
				//初速*時間+(重力加速度*時間)/2
				tmpvec.y += -2 * (100 * bulletCon_[i] / 60 + static_cast<float>(S_GRAVITY * bulletCon_[i] / 60) * 2 / 2);
				//判定処理　
				if (tmpvec.y < -80)
				{
					shotflag_[i] = false;
				}
				pos_[i] = tmpvec;

				if (lpobjlMng.ObjCollHit(pos_[i], BuniD_))
				{
					lpSceneMng.SetEffect(EffectName::testef, pos_[i]);
					shotflag_[i] = false;
				}
				bulletCon_[i] = 0;
			}
			bulletCon_[i]++;
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (shotflag_[i] == true)
		{
			//座標設定
			lpobjlMng.Setobjpos(pos_[i], direction_[i], UNIT_ID::BULLET, i);
			//描画に投げる
			lpobjlMng.ObjDraw(UNIT_ID::BULLET, i);
		}
	}
	bcon_++;
}

void Bullet::SetBullet(VECTOR pos, VECTOR vec, int non, int pnum)
{
	if (bcon_ <= 60 * 6)
	{
		return;
	}
	int i = pnum;
	//for (int i = 0; i < BULLETMAX; i++)
	//{
	//	if (bulletCon_[i] / 60 == 0)
	//	{
	//		return;
	//	}
	//}
	if (i < BULLETMAX)
	{
		if (shotflag_[i] == false)
		{
			MATRIX tmpmat;
			VECTOR tvec = vec;	
			tvec.x *= 200;
			tvec.z *= 200;
			if (non == 0)
			{
				tmpmat = MGetRotY(static_cast<float>((DX_PI / 180) * -90));

			}
			else if (non == 1)
			{
				tmpmat = MGetRotY(static_cast<float>((DX_PI / 180) * 90));
				//tvec.x *= 500;
				//tvec.z *= 500;
			}
			pos_[i] = VAdd(pos, tvec);
			pos_[i].y = 120;
			direction_[i] = VNorm(VTransform(vec, tmpmat));
			direction_[i].x *= -50;
			direction_[i].z *= -50;
			direction_[i].y = 0;
			bulletCon_[i] = 0;
			shotflag_[i] = true;
			VECTOR tmp = VSub(lpSceneMng.campos_, pos);
			tmp.x *= tmp.x;
			tmp.y *= tmp.y;
			tmp.z *= tmp.z;
			float tf = tmp.x + tmp.y + tmp.z;
			tf *= tf;
			lpSudlMng.AddSE(std::string("sound/bann.wav"), pos_[i], tf);
		}
	}
	//for (int i = 0; i < BULLETMAX; i++)
	//{
	//	//MATRIX tmpmat;
	//	//if (BULLETMAX / 2 < i)
	//	//{
	//	//	tmpmat = MGetRotY(static_cast<float>((DX_PI / 180) * -90));
	//	//}
	//	//else
	//	//{
	//	//	tmpmat = MGetRotY(static_cast<float>((DX_PI / 180) * 90));
	//	//}
	//	VECTOR tvec = vec;
	//	if (i == 0)
	//	{
	//		tvec.x *= 200;
	//		tvec.z *= 200;
	//	}
	//	else if (i == 1)
	//	{
	//		tvec.x *= 5000;
	//		tvec.z *= 500;
	//	}

	//	pos_[i] = VAdd(pos, tvec);
	//	pos_[i].y = 120;
	//	tvec = vec;
	//	tvec.x *= 200;
	//	tvec.z *= 200;
	//	direction_[i] = non;
	//	direction_[i].x *= -200;
	//	direction_[i].z *= -200;
	//	direction_[i].y = 0;
	//	bulletCon_[i] = 0;
	//	shotflag_[i] = true;

	//}
}

