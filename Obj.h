#pragma once
#include "Dxlib.h"
#include<memory>

class Obj;

using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	~Obj();
	virtual void Updata(void) = 0;
};

