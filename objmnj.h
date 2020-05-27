#pragma once
#define CPU_MAX 2
#include "obj.h"
#include "Bullet.h"


#define CHARA_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
#define CHARA_ENUM_DEFAULT_SIZE		3000.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
#define CHARA_HIT_WIDTH				3000.0f		// 当たり判定カプセルの半径
#define CHARA_HIT_HEIGHT			1000.0f		// 当たり判定カプセルの高さ
#define CHARA_HIT_PUSH_POWER		40.0f		// キャラクター同士で当たったときの押し出される力

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

	void Setobjpos(VECTOR pos, VECTOR vec, UNIT_ID id, int num);

	int Getobjpos(VECTOR pos, UNIT_ID id, int num);

	UNIT_ID CheckHit(UNIT_ID id, int num);

	void TryHit(void);

	void ObjDraw(UNIT_ID id, int num);

	void ObjRotation(UNIT_ID id,float moveangle, int num);

	void ObjCollHit(VECTOR pos, VECTOR* moveVec,UNIT_ID id);

private:
	static Objmnj* sInstance;

	int		playerobj;				//ﾌﾟﾚｲﾔモデル格納用
	int		skyobj;					//空
	int		enemyobj;				//敵モデル格納用
	int		bulletobj;				//弾モデル格納用
	int		bulletmodel[BULLETMAX];	//弾モデル格納(多数)用
	int		mapmodel;				//海モデル格納用
	VECTOR	pvec;
	VECTOR	evec;
	VECTOR	bvec[BULLETMAX];
	VECTOR	ppos;
	VECTOR	epos;
	VECTOR	bpos[BULLETMAX];

	UNIT_ID	player;					//ﾌﾟﾚｲﾔモデル格納用
	UNIT_ID	enemy;					//敵モデル格納用
	UNIT_ID	bullet[BULLETMAX];		//弾

	MV1_COLL_RESULT_POLY_DIM pHit;
	MV1_COLL_RESULT_POLY_DIM eHit;

	Objmnj();
	~Objmnj();
};

