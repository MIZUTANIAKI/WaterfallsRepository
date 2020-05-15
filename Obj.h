#pragma once
#include "Dxlib.h"
#include<memory>

enum class UNIT_ID			//���ꂼ��̗���
{
	PLAYER,
	CPU,
	MAX,
};


class Obj;

using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	~Obj();
	virtual UNIT_ID GetUnitID(void)
	{
		return _unitID;
	}
	virtual VECTOR GetPos(void)
	{
		return _pos;
	}
	virtual void Updata(void) = 0;

	void SetUnitID(UNIT_ID unitID) { _unitID = unitID; }
protected:
	VECTOR _pos;
	UNIT_ID _unitID;
};

