#pragma once

#define lpSceneMng SceneMng::GetInstance()

class sceneMng
{
public:
	
	static sceneMng& GetInstance(void)
	{
		
		Create();
		return *sInstance;
	}
	
	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new sceneMng();
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


	void Run(void);
private:
	static sceneMng* sInstance;
	bool SysInit();
	sceneMng();
	~sceneMng();
};

