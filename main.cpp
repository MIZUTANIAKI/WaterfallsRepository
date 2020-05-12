#include <DxLib.h>
#include "Scene/sceneMng.h"

int main()
{
	sceneMng::Create();
	sceneMng::GetInstance().Run();
	sceneMng::GetInstance().Destroy();

	DxLib_End();
	return 0;
}