#pragma once
#include <vector>
#include <memory>

#define lpMapMng Map::GetInstance()

class Map
{
public:
	static Map& GetInstance(void)	//実体を、呼び出す？処理
	{
		Create();						//動的に作るときに使う
		return *sInstance;
	}
	static void Create(void)			//動的に、実体を作るための処理
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
			delete sInstance;	//削除する	
		}
		sInstance = nullptr;	//ｱﾄﾞﾚｽが、ごみとして残っているのできれいにする
	}

	//bool IsHitmapobj(int mh, VECTOR pos, VECTOR MoveVector, int height, int width);

	void Update(void);

private:
	Map();
	~Map();
	int mapmodel;
	static Map* sInstance;		//動的に作るために、ﾎﾟｲﾝﾀｰで、実体が入るものを作る

};

