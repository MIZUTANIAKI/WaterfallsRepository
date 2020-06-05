#pragma once
#include "BaseScene.h"
#include <vector>
#include "obj.h"
#include<memory>
#include "../camera.h"


class GameScene :
	public BaseScene
{
public:
	unique_Base Update(unique_Base own) override;		//�V�[�����A�X�V����B
	GameScene();
	~GameScene();
private:
	Camera cam;											//�J�����N���X�i�[
	std::vector<std::pair<shardObj, UNIT_ID>> _objList;	//�A���C�u�ɂȂ��Ă��鑶�݂��Ǘ�����B
	VECTOR ppos;										//�v���C���[���W�n���p
};

