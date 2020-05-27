#pragma once
#define CPU_MAX 2
#include "obj.h"
#include "Bullet.h"


#define CHARA_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔
#define CHARA_ENUM_DEFAULT_SIZE		3000.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
#define CHARA_HIT_WIDTH				3000.0f		// �����蔻��J�v�Z���̔��a
#define CHARA_HIT_HEIGHT			1000.0f		// �����蔻��J�v�Z���̍���
#define CHARA_HIT_PUSH_POWER		40.0f		// �L�����N�^�[���m�œ��������Ƃ��̉����o������

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

	int		playerobj;				//��ڲԃ��f���i�[�p
	int		skyobj;					//��
	int		enemyobj;				//�G���f���i�[�p
	int		bulletobj;				//�e���f���i�[�p
	int		bulletmodel[BULLETMAX];	//�e���f���i�[(����)�p
	int		mapmodel;				//�C���f���i�[�p
	VECTOR	pvec;
	VECTOR	evec;
	VECTOR	bvec[BULLETMAX];
	VECTOR	ppos;
	VECTOR	epos;
	VECTOR	bpos[BULLETMAX];

	UNIT_ID	player;					//��ڲԃ��f���i�[�p
	UNIT_ID	enemy;					//�G���f���i�[�p
	UNIT_ID	bullet[BULLETMAX];		//�e

	MV1_COLL_RESULT_POLY_DIM pHit;
	MV1_COLL_RESULT_POLY_DIM eHit;

	Objmnj();
	~Objmnj();
};

