#pragma once
#include <vector>
#include <tuple>
#include <DxLib.h>
#include "BaseScene.h"
#include "../vector2.h"

#define lpSceneMng SceneMng::GetInstance()

using 	BulletQueT = std::tuple<VECTOR, int>;

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



	void AddDrawQue(int que);						//通常描画処理
	void AddDrawQuenex(int que);					//透過用描画処理

	void Run(void);									//実行処理

	const Vector2 ScreenSize;						//画面サイズ

	void AddBulletQue(BulletQueT bque);				//弾のキュー

	std::vector < BulletQueT> GetBulletList(void);	//弾のリストを渡す用　いらないかも



private:
	bool systemEnd;									//**未作成**終了するを、押した場合

	int _fcon;										//フレームカウント
	static SceneMng* sInstance;						//シーンマネージャーの静的な宣言
	bool SysInit();									//初期化
	unique_Base _activeScene;						//今動いてるsceneが入る。

	int LightHandle;								//あかり1通常ライト
	int LightHandle2;								//あかり2通常ライト

	std::vector<int> _drawList;						//描画するものを溜めておくキュー
	std::vector<int> _drawListnex;					//描画するものを溜めておくキュー（すける）
	std::vector<BulletQueT> _BulletList;			//弾丸キュー
	void Draw(void);								//描画処理
	SceneMng();
	~SceneMng();

};

