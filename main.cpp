#include <DxLib.h>
#include "Scene/sceneMng.h"
#include "objmnj.h"
#include <EffekseerForDXLib.h>

/* �����Ȃ��Ƃ��͂����Ƃ�86�ɂȂ��Ă��邩�m�F */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,LPSTR lpszCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);										//���windowӰ��
	if (DxLib_Init() == -1)										//DXײ���؂̏���������
	{
		return false;
	}
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (Effekseer_Init(8000) == -1)
	{
		return false;
	}

	SceneMng::Create();
	SceneMng::GetInstance().Run();
 	SceneMng::GetInstance().Destroy();

	DxLib_End();
	return 0;
}