#pragma once
#include "cAnimalNode.h"

class cAnimalBody : public cAnimalNode
{
public:
	cAnimalBody();
	~cAnimalBody();

	virtual void Setup() override;
};

