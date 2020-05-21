#pragma once
#include "Dxlib.h"
#include "Obj.h"


class Enemy :
	public Obj
{
public:

	Enemy();
	~Enemy();

	UNIT_ID GetUnitID(void) override
	{
		return _unitID;
	}
	VECTOR GetPos(void) override
	{
		return _pos;
	}

	void Updata(void) override;

private:
	int _model;
	VECTOR _pos;
	UNIT_ID _unitID;

};

