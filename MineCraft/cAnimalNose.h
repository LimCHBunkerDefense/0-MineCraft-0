#pragma once
#include "cAnimalNode.h"

class cAnimalNose : public cAnimalNode
{
public:
	cAnimalNose();
	~cAnimalNose();

	virtual void Setup() override;
};

