#include <time.h>
#include "GameScene.h"
#include "Player.h"
#include "SceneMng.h"

GameScene::GameScene()
{


	_objList.emplace_back(new(Player));

	srand((unsigned)time(NULL));								//���Ԃ��g���ă����_���ɐ��������ւ���
}

unique_Base GameScene::Update(unique_Base own)
{
	for (auto data : _objList)
	{
		(*data).Updata();	//�X�V����
	}

	return std::move(own);
}


GameScene::~GameScene()
{
}
