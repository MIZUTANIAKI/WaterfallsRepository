#include<DxLib.h>
#include "sceneMng.h"
#include "GameScene.h"

sceneMng* sceneMng::sInstance = nullptr;

sceneMng::sceneMng()
{
}

sceneMng::~sceneMng()
{
}

void sceneMng::Run(void)
{
	if (SysInit() != true)
	{
		return;
	}
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
	}
}

bool sceneMng::SysInit(void)
{
	SetGraphMode(1920, 1080, 16);
	ChangeWindowMode(true);										//‰æ–ÊwindowÓ°ÄŞ
	if (DxLib_Init() == -1)										//DX×²ÌŞ×Ø‚Ì‰Šú‰»ˆ—
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetCreate3DSoundFlag(false);
	SetFontSize(60);
	
	return true;
}
