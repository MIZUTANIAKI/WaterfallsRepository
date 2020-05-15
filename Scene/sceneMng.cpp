#include<DxLib.h>
#include "sceneMng.h"
#include "GameScene.h"

SceneMng* SceneMng::sInstance = nullptr;


SceneMng::SceneMng() :ScreenSize{1920,1080}
{
	_fcon = NULL;
}

SceneMng::~SceneMng()
{
}

void SceneMng::AddDrawQue(int que)
{
	//•`‰æ—p‚ÌQue‚ğ’Ç‰Á
	_drawList.emplace_back(que);
}

void SceneMng::AddDrawQuenex(int que)
{
	//•`‰æ—p‚ÌQue‚ğ’Ç‰Á
	_drawListnex.emplace_back(que);
}

void SceneMng::Draw(void)
{
	ClsDrawScreen();

		//ˆê‚Â‚¸‚Â•`‰æ
	for (auto dQue : _drawList)
	{
		MV1DrawModel(dQue);
	}

	//‚·‚¯‚é‚Ì‚ğ•`‰æ
	for (auto dQue : _drawListnex)
	{
		MV1DrawModel(dQue);
	}
	DrawSphere3D(VGet(0.0f, 0.0f, 0.0f), 100.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);	//’Êí•¨‚ğ‚·‚×‚Ä•`‰æŒãAƒKƒ‰ƒX‚È‚Ç‚Ì“§‚¯‚½‚¢‚à‚Ì‚ğ•`‰æ‚·‚é‚Æ‚¢‚¢



	ScreenFlip();
}

void SceneMng::Run(void)
{
	if (SysInit() != true)
	{
		return;
	}
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_drawList.clear();
		_drawListnex.clear();
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();
		_fcon++;
	}
}

bool SceneMng::SysInit(void)
{
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);										//‰æ–ÊwindowÓ°ÄŞ
	if (DxLib_Init() == -1)										//DX×²ÌŞ×Ø‚Ì‰Šú‰»ˆ—
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetCreate3DSoundFlag(false);
	SetFontSize(60);
	SetBackgroundColor(100, 255, 255);
	SetUseZBufferFlag(TRUE);
	SetCameraNearFar(100.0f, 100.0f);
	SetMouseDispFlag(false);	//ƒ}ƒEƒX‚ğ”ñ•\¦‚É
	return true;
}
