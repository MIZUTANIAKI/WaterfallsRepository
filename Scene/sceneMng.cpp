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
	//�`��p��Que��ǉ�
	_drawList.emplace_back(que);
}

void SceneMng::AddDrawQuenex(int que)
{
	//�`��p��Que��ǉ�
	_drawListnex.emplace_back(que);
}

void SceneMng::Draw(void)
{
	ClsDrawScreen();

		//����`��
	for (auto dQue : _drawList)
	{
		MV1DrawModel(dQue);
	}

	//������̂�`��
	for (auto dQue : _drawListnex)
	{
		MV1DrawModel(dQue);
	}
	DrawSphere3D(VGet(0.0f, 0.0f, 0.0f), 100.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);	//�ʏ함�����ׂĕ`���A�K���X�Ȃǂ̓����������̂�`�悷��Ƃ���



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
	ChangeWindowMode(true);										//���windowӰ��
	if (DxLib_Init() == -1)										//DXײ���؂̏���������
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetCreate3DSoundFlag(false);
	SetFontSize(60);
	SetBackgroundColor(100, 255, 255);
	SetUseZBufferFlag(TRUE);
	SetCameraNearFar(100.0f, 100.0f);
	SetMouseDispFlag(false);	//�}�E�X���\����
	return true;
}
