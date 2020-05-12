#include <time.h>
#include "GameScene.h"
#include "Player.h"
#include "SceneMng.h"

GameScene::GameScene()
{


	_objList.emplace_back(new(Player));

	srand((unsigned)time(NULL));								//時間を使ってランダムに数字を入れ替える
}

unique_Base GameScene::Update(unique_Base own)
{
	for (auto data : _objList)
	{
		(*data).Updata();	//更新処理
	}

	return std::move(own);
}


GameScene::~GameScene()
{
}
