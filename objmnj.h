#pragma once
#define CPU_MAX 2
#include "obj.h"


#define lpobjlMng Objmnj::GetInstance()

class Objmnj
{
public:
	static Objmnj& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Objmnj();
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




private:
	static Objmnj* sInstance;
	Objmnj();
	~Objmnj();
};

