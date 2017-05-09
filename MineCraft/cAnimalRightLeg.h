#pragma once
#include "cAnimalNode.h"

class cAnimalRightLeg : public cAnimalNode
{
public:
	cAnimalRightLeg();
	~cAnimalRightLeg();

	virtual void Setup() override;
};

