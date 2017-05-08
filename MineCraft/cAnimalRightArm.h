#pragma once
#include "cAnimalNode.h"

class cAnimalRightArm : public cAnimalNode
{
public:
	cAnimalRightArm();
	~cAnimalRightArm();

	virtual void Setup() override;
};

