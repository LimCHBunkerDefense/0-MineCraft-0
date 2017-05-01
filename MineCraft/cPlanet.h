#pragma once
#include "cCubePNT.h"

class cPlanet : public cCubePNT
{
public:
	cPlanet();
	~cPlanet();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

