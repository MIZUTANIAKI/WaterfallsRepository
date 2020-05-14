#pragma once
#include "BaseScene.h"
#include <vector>
#include "obj.h"
#include<memory>


class GameScene :
	public BaseScene
{
public:
	unique_Base Update(unique_Base own) override;			//シーンを、更新する。
	GameScene();
	~GameScene();
private:

	std::vector<std::pair<shardObj, UNIT_ID>> _objList;	//アライブになっている存在を管理する。
};

