#pragma once
#include <vector>
#include <memory>

#define lpMapMng Map::GetInstance()

class Map
{
public:
	static Map& GetInstance(void)	//���̂��A�Ăяo���H����
	{
		Create();						//���I�ɍ��Ƃ��Ɏg��
		return *sInstance;
	}
	static void Create(void)			//���I�ɁA���̂���邽�߂̏���
	{
		if (sInstance == nullptr)
		{
			sInstance = new Map();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;	//�폜����	
		}
		sInstance = nullptr;	//���ڽ���A���݂Ƃ��Ďc���Ă���̂ł��ꂢ�ɂ���
	}

	//bool IsHitmapobj(int mh, VECTOR pos, VECTOR MoveVector, int height, int width);

	void Update(void);

private:
	Map();
	~Map();
	int mapmodel;
	static Map* sInstance;		//���I�ɍ�邽�߂ɁA�߲����ŁA���̂�������̂����

};

