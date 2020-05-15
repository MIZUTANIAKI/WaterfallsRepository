#pragma once
#include <vector>
#include <tuple>
#include <DxLib.h>
#include "BaseScene.h"
#include "../vector2.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	
	static SceneMng& GetInstance(void)
	{
		
		Create();
		return *sInstance;
	}
	
	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	int GetFcon(void) 
	{
		return _fcon; 
	}

	void AddDrawQue(int que);
	void AddDrawQuenex(int que);

	void Run(void);

	const Vector2 ScreenSize;
private:

	int _fcon;
	static SceneMng* sInstance;
	bool SysInit();
	unique_Base _activeScene;

	std::vector<int> _drawList;	//描画するものを溜めておくキュー
	std::vector<int> _drawListnex;	//描画するものを溜めておくキュー（すける）
	void Draw(void);

	SceneMng();
	~SceneMng();
};

