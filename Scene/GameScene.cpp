#include <time.h>
#include "objmnj.h"
#include "Player.h"
#include "enemy.h"
#include "SceneMng.h"
#include "Obj.h"
#include "Bullet.h"
#include "GameScene.h"
#include "ImgMnj.h"
#include "MenuScene.h"
#include "PadMng.h"
#include "SoundMnj.h"


GameScene::GameScene()
{
	_objList.emplace_back(new(Player),UNIT_ID::PLAYER);
	_objList.emplace_back(new(Enemy), UNIT_ID::CPU);
	_objList.emplace_back(new(Enemy), UNIT_ID::CPU);
	_objList.emplace_back(new(Enemy), UNIT_ID::CPU);
	ppos = VGet(0.0f, 0.0f, 0.0f); 
	srand((unsigned)time(NULL));								//時間を使ってランダムに数字を入れ替える
	gcon_ = 0;
	scnID_ = SCN_GAME;
	lpSudlMng.CheckSEList(std::string("sound/bann.wav"));
	cpy_ = 200;
	lrSF_ = 0;
}

UNBS GameScene::Update(UNBS own)
{
	if (LpPadMng.GetPad().Buttons[7])
	{
		return std::make_unique<MenuScene>(std::move(own));
	}


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
				lrSF_ = (*data.first).GetSLR()^1;
		}
	}


	if (lpSceneMng.GetFcon() / 60 % 2 == 0)
	{
		cpy_ -= 0.2f;
	}
	else
	{
		cpy_ += 0.2f;
	}
	lpobjlMng.Setobjpos(VGet(500.0f, cpy_ - 200, 0.0f), VGet(0.0f, 0.0f, 0.0f), UNIT_ID::NON, 0);
	if (gcon_ <= 60 * 6)
	{
		lpImglMng.AddImg(std::string("img/sous3.png"), lpSceneMng.ScreenSize / 2);
	}
	else
	{
		lpImglMng.AddImg(std::string("img/lr.png"), lpSceneMng.ScreenSize / 2, lrSF_);
	}
	gcon_++;
	return std::move(own);
}


GameScene::~GameScene()
{
	lpobjlMng.Destroy();
}

void GameScene::Draw(void)
{
	lpobjlMng.DrawNaw();
	lpImglMng.Draw(); 
	if (gcon_ <= 60 * 6)
	{
		DxLib::DrawFormatString(0, 0, 0x000000, "あと[ %d ]秒で始まるよ", (3 - gcon_ / 120));
	}
}

SCN_ID GameScene::GetSCNID_(void)
{
	return scnID_;
}

