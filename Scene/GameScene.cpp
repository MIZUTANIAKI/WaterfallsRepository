#include <time.h>
#include "objmnj.h"
#include "Player.h"
#include "enemy.h"
#include "SceneMng.h"
#include "../Obj.h"
#include "../Bullet.h"
#include "GameScene.h"

GameScene::GameScene()
{
	_objList.emplace_back(new(Player),UNIT_ID::PLAYER);
	_objList.emplace_back(new(Enemy), UNIT_ID::CPU);
	ppos = VGet(0.0f, 0.0f, 0.0f);
	srand((unsigned)time(NULL));								//時間を使ってランダムに数字を入れ替える
}

unique_Base GameScene::Update(unique_Base own)
{
	for (auto data : _objList)
	{
		if (data.second == UNIT_ID::CPU)
		{
			(*data.first).Updata(ppos);	//更新処理
		}
		(*data.first).Updata();	//更新処理
		if (data.second == UNIT_ID::PLAYER)
		{
				cam.CameraRun((*data.first).GetPos());
				ppos = (*data.first).GetPos();
		}
	}
	return std::move(own);
}


GameScene::~GameScene()
{
	lpobjlMng.Destroy();
}

