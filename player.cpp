#include <DxLib.h>
#include "player.h"

Player::Player()
{
	_pos = VGet(0.0f, 0.0f, 0.0f);
	playerobj = NULL;
}

Player::~Player()
{
}

void Player::Updata(void)
{
	_pos.z = MOVESPEED;
}
