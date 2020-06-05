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



	void AddDrawQue(int que);						//�ʏ�`�揈��
	void AddDrawQuenex(int que);					//���ߗp�`�揈��

	void Run(void);									//���s����

	const Vector2 ScreenSize;						//��ʃT�C�Y

	void AddBulletQue(BulletQueT bque);				//�e�̃L���[

	std::vector < BulletQueT> GetBulletList(void);	//�e�̃��X�g��n���p�@����Ȃ�����



private:
	bool systemEnd;									//**���쐬**�I��������A�������ꍇ

	int _fcon;										//�t���[���J�E���g
	static SceneMng* sInstance;						//�V�[���}�l�[�W���[�̐ÓI�Ȑ錾
	bool SysInit();									//������
	unique_Base _activeScene;						//�������Ă�scene������B

	int LightHandle;								//������1�ʏ탉�C�g
	int LightHandle2;								//������2�ʏ탉�C�g

	std::vector<int> _drawList;						//�`�悷����̂𗭂߂Ă����L���[
	std::vector<int> _drawListnex;					//�`�悷����̂𗭂߂Ă����L���[�i������j
	std::vector<BulletQueT> _BulletList;			//�e�ۃL���[
	void Draw(void);								//�`�揈��
	SceneMng();
	~SceneMng();

};

