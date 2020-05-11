#include <iostream>
#include <DxLib.h>
#include "sceneMng.h"

int main()
{
	std::cout << "Hello World!\n";
	sceneMng::Create();
	sceneMng::GetInstance().Run();
	sceneMng::GetInstance().Destroy();

	DxLib_End();
	return 0;
}