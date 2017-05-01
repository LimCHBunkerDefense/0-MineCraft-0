#pragma once
#include "cPlanet.h"

class cSun : public cPlanet
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMtl;

public:
	cSun();
	~cSun();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void Set_Material();
};

