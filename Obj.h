#pragma once
#include "Dxlib.h"
#include<memory>

enum class UNIT_ID			//���ꂼ��̗���
{
	PLAYER,	//�v���C���[�L����
	CPU,	//�v���C���[���삶��Ȃ��L����
	BULLET,	//�e
	NON,	//������
	MAX,	
};


class Obj;

using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	~Obj();
	virtual UNIT_ID GetUnitID(void)	//���j�b�gID��Ԃ�
	{
		return _unitID;
	}
	virtual VECTOR GetPos(void)	//�ʒu����Ԃ�
	{
		return _pos;
	}

	virtual void Updata(void) = 0;	//OBJ�n�̍X�V�p

	virtual void Updata(VECTOR pos)	//OBJ�n�̍X�V�p2�ق���OBJ�n�̍��W�Ȃǂ�����ꍇ
	{
		return;
	}

	void SetUnitID(UNIT_ID unitID) { _unitID = unitID; }
protected:
	VECTOR _pos;	//���W�i�[
	UNIT_ID _unitID;	//���j�b�gID�i�[
};

