#include <DxLib.h>
#include "Scene/sceneMng.h"
#include "objmnj.h"
#include <EffekseerForDXLib.h>

/* “®‚©‚È‚¢‚Æ‚«‚Í‚¿‚á‚ñ‚Æ‚˜86‚É‚È‚Á‚Ä‚¢‚é‚©Šm”F */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,LPSTR lpszCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);										//‰æ–ÊwindowÓ°ÄŞ
	if (DxLib_Init() == -1)										//DX×²ÌŞ×Ø‚Ì‰Šú‰»ˆ—
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