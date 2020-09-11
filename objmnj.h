#pragma once
#define CPU_MAX 2
#include "obj.h"
#include "Bullet.h"


//#define CHARA_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔
//#define CHARA_ENUM_DEFAULT_SIZE		3000.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
//#define CHARA_HIT_WIDTH				3000.0f		// �����蔻��J�v�Z���̔��a
//#define CHARA_HIT_HEIGHT			1000.0f		// �����蔻��J�v�Z���̍���
//#define CHARA_HIT_PUSH_POWER		40.0f		// �L�����N�^�[���m�œ��������Ƃ��̉����o������

#define lpobjlMng Objmnj::GetInstance()

//���f���Ǘ��}�l�[�W��
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
	
	void DrawNaw(void);

	void ReSetD(void);	//���t���[���ŏ��ɌĂ�

	void Setobjpos(VECTOR pos, VECTOR vec, UNIT_ID id, int num);	//�ʒu�����Z�b�g id�ŁA����

	int Getobjpos(VECTOR pos, UNIT_ID id, int num);					//�ʒu����Ԃ��B

	UNIT_ID CheckHit(UNIT_ID id, int num);							//���������Ă邩�m�F�p**���ݎg�p�s��**								

	void ObjDraw(UNIT_ID id, int num);								//������ĂԂƁA�`��v�����Ascene�}�l�[�W���ɂ��܂�

	void ObjRotation(UNIT_ID id,float moveangle, int num);			//��]���i�����ځj���Z�b�g

	bool ObjCollHit(VECTOR pos, UNIT_ID id);		//�����蔻��`�F�b�N�p

private:
	static Objmnj* sInstance;


	std::vector<int> _drawList;						//�`�悷����̂𗭂߂Ă����L���[
	std::vector<int> _drawListnex;					//�`�悷����̂𗭂߂Ă����L���[�i������j

	int		issobj;				//��ڲԃ��f���i�[�p
	int		playerobj;				//��ڲԃ��f���i�[�p
	int		playerobjsub[BULLETMAX];//��ڲԃ��f���i�[�p
	int		phitobj;				//��ڲԓ����蔻�胂�f���i�[�p
	int		skyobj;					//��
	int		enemyobj;				//�G���f���i�[�p
	int		enemytmodel[BULLETMAX];				//�G���f���i�[�p
	int		ehitobj;				//�����蔻�胂�f���i�[�p
	int		bulletobj;				//�e���f���i�[�p
	int		bulletmodel[BULLETMAX];	//�e���f���i�[(����)�p
	int		mapmodel;				//�C���f���i�[�p
	VECTOR	pvec;					//�v���C���ړ��x�N�g��
	VECTOR	evec[BULLETMAX];		//�G�̈ړ��x�N�g��
	VECTOR	bvec[BULLETMAX];		//�e�̈ړ��x�N�g��
	VECTOR	ppos;					//�v���C���[���W
	VECTOR	epos[BULLETMAX];					//�G���W
	VECTOR	bpos[BULLETMAX];		//�e���W

	UNIT_ID	player;					//��ڲԃ��f���i�[�p
	UNIT_ID	enemy;					//�G���f���i�[�p
	UNIT_ID	bullet[BULLETMAX];		//�e

	Objmnj();
	~Objmnj();
};

