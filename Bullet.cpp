#include <iostream>
#include <DxLib.h>
#include "Scene/sceneMng.h"
#include "Bullet.h"


Bullet::Bullet()
{
	_Shotflag = false;
	bulletobj = MV1LoadModel("mv/bullet.mv1");
	for (int i = 0; i < 2; i++)
	{
		bulletmodel[i] = MV1DuplicateModel(bulletobj);
	}
}

Bullet::~Bullet()
{
}

void Bullet::Run(void)
{
	if (_Shotflag == true)
	{
		for (int i = 0; i < 2; i++)
		{
			VECTOR tmpvec, tmpmove;
			tmpmove.x = _direction[i].x * 100;
			tmpmove.z = _direction[i].z * 100;
			tmpmove.y = 0.0f;
			tmpvec = VAdd(_pos[i], tmpmove);
			//tmpvec = VAdd(_pos[i], VGet(0.0f, S_GRAVITY, 0.0f));
		
			//”»’èˆ—@


			_pos[i] = tmpvec;
		}
		for (int i = 0; i < 2; i++)
		{
			MV1SetPosition(bulletmodel[i], _pos[i]);
			lpSceneMng.AddDrawQue(bulletmodel[i]);	//•`‰æ—v‹
		}
	}

}

void Bullet::SetBullet(VECTOR pos, VECTOR vec)
{
	MATRIX tmpmat;

	tmpmat = MGetRotY((DX_PI / 180) * -90);

	_pos[0] = pos;
	_direction[0] = VTransform(vec, tmpmat);

	tmpmat = MGetRotY((DX_PI / 180) * 90);
	_pos[1] = pos;
	_direction[1] = VTransform(vec,tmpmat);

	_Shotflag = true;
}

