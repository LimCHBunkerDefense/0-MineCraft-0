#pragma once
#include "cAnimalNode.h"

class cAnimalHead : public cAnimalNode
{
public:
	cAnimalHead();
	~cAnimalHead();

	virtual void Setup() override;
};

