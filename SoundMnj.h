#pragma once
#include <vector>
#include <DxLib.h>
#include "Vector2.h"
#include <string>
#include <map>

#define lpSudlMng SoundMnj::GetInstance()

class SoundMnj
{
public:
	static SoundMnj& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SoundMnj();
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

	void ResetD(void);

	void AddBGM(std::string que);

	void AddSE(std::string que, VECTOR pos, float Dis);
	
	void Run(void);

	bool CheckSEList(std::string que);//指定したSEをすでに読み込んであるか調べる
private:
	static SoundMnj* sInstance;

	std::vector <std::pair<std::string,std::pair<VECTOR,float>>> seList_;					//SEを溜めておくキュー
	std::map<std::string, int> seHMap_;

	int bgmH_;

	SoundMnj();
	~SoundMnj();
};

