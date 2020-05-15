#include <time.h>
#include "GameScene.h"
#include "Player.h"
#include "SceneMng.h"
#include "../map.h"
#include "../Obj.h"

GameScene::GameScene()
{
	_objList.emplace_back(new(Player),UNIT_ID::PLAYER);
	

	srand((unsigned)time(NULL));								//時間を使ってランダムに数字を入れ替える

	lpMapMng;
}

unique_Base GameScene::Update(unique_Base own)
{
	for (auto data : _objList)
	{
		(*data.first).Updata();	//更新処理
		if (data.second == UNIT_ID::PLAYER)
		{
			cam.CameraRun((*data.first).GetPos());
		}
	}


	lpMapMng.Update();
	return std::move(own);
}


GameScene::~GameScene()
{
}
