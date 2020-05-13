#include <DxLib.h>
#include "Scene/sceneMng.h"

int main()
{
	SceneMng::Create();
	SceneMng::GetInstance().Run();
	SceneMng::GetInstance().Destroy();

	DxLib_End();
	return 0;
}