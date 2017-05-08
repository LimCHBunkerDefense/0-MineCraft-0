#pragma once
#include "cAnimalNode.h"

class cAnimalLeftLeg : public cAnimalNode
{
public:
	cAnimalLeftLeg();
	~cAnimalLeftLeg();

	virtual void Setup() override;
};

