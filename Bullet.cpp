#include <iostream>
#include <DxLib.h>
#include "Scene/sceneMng.h"
#include "Bullet.h"
#include "objmnj.h"

//斜め下に打つのではなく、楕円描きながら落としたい
//水平に、等速直線運動して、下向きに自由落下している状態らしい
//等速は、速度が、一定のまま進んでいく。
//自由落下、重力加速度は9.8[m/s²]で固定。
//つまり初速*時間+(重力加速度*時間)/2？

Bullet::Bullet()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		_Shotflag[i] = false;
		_bulletCon[i] = 0;
		_pos[i] = VGet(0.0f, 0.0f, 0.0f);
		_direction[i] = VGet(0.0f, 0.0f, 0.0f);
	}
}

Bullet::~Bullet()
{
}

void Bullet::Run(void)
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_Shotflag[i] == true)
		{
			VECTOR tmpvec, tmpmove;
			tmpmove.x = _direction[i].x;
			tmpmove.z = _direction[i].z;
			tmpmove.y = 0.0f;
			tmpvec = VAdd(_pos[i], tmpmove);
			//初速*時間+(重力加速度*時間)/2
			tmpvec.y += -1*(100 * _bulletCon[i]/60 + static_cast<float>(S_GRAVITY * _bulletCon[i]/60)*2 / 2);
			//判定処理　
			if (tmpvec.y < 0)
			{
				_Shotflag[i] = false;
			}
			_pos[i] = tmpvec;
			_bulletCon[i]++;
		}
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_Shotflag[i] == true)
		{
			//座標設定
			lpobjlMng.Setobjpos(_pos[i], _direction[i], UNIT_ID::BULLET, 0);
			//描画に投げる
			lpobjlMng.ObjDraw(UNIT_ID::BULLET, i);
		}
	}

}

void Bullet::SetBullet(VECTOR pos, VECTOR vec)
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_Shotflag[i] == false)
		{
			MATRIX tmpmat;
			if (BULLETMAX / 2 < i)
			{
				tmpmat = MGetRotY(static_cast<float>((DX_PI / 180) * -90));
			}
			else
			{
				tmpmat = MGetRotY(static_cast<float>((DX_PI / 180) * 90));
			}
			_pos[i] = pos;
			_pos[i].y = 800;
			_direction[i] = VNorm(VTransform(vec, tmpmat));
			_direction[i].x *= 100;
			_direction[i].z *= 100;
			_bulletCon[i] = 0;
			_Shotflag[i] = true;
		}
	}
}

