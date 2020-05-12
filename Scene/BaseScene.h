#pragma once
#include<memory>
class BaseScene;
using unique_Base = std::unique_ptr<BaseScene>;
class BaseScene
{
public:
	BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;	//�V�[�����A�X�V����B
	virtual ~BaseScene();
};