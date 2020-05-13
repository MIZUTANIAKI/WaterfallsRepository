#pragma once
#include <vector>
#include <tuple>
#include <DxLib.h>
#include "BaseScene.h"

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

	void AddDrawQue(int que);
	void AddDrawQuenex(int que);

	void Run(void);
private:
	static SceneMng* sInstance;
	bool SysInit();
	unique_Base _activeScene;

	std::vector<int> _drawList;	//�`�悷����̂𗭂߂Ă����L���[
	std::vector<int> _drawListnex;	//�`�悷����̂𗭂߂Ă����L���[�i������j
	void Draw(void);

	SceneMng();
	~SceneMng();
};

