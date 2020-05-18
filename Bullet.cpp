#include <iostream>
#include <DxLib.h>
#include "Scene/sceneMng.h"
#include "Bullet.h"


Bullet::Bullet()
{
	_Shotflag = false;
	bulletobj = MV1LoadModel("mv/pShip.mv1");
}

Bullet::~Bullet()
{
}

void Bullet::Run(void)
{
	if (_Shotflag == true)
	{
		VECTOR tmpvec,tmpmove;
		tmpmove.x = _direction.x * 100;
		tmpmove.z = _direction.z * 100;
		tmpmove.y = 0.0f;
		tmpvec = VAdd(_pos, tmpmove);

		//tmpvec = VAdd(_pos, VGet(0.0f, S_GRAVITY, 0.0f));

		//îªíËèàóùÅ@
		
		_pos = tmpvec;

		MV1SetPosition(bulletobj, _pos);

		lpSceneMng.AddDrawQue(bulletobj);	//ï`âÊóvãÅ
	}

}

void Bullet::SetBullet(VECTOR pos, VECTOR vec)
{
	_pos = pos;
	_direction = vec;
	_Shotflag = true;
}

