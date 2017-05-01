#pragma once
#include "cPlanet.h"

class cSun : public cPlanet
{
private:
	cCubePNT*			m_pSun;
	D3DXVECTOR3			m_vPosition;

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMtl;

public:
	cSun();
	~cSun();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual D3DXVECTOR3& GetPosition();
	void Set_Material();
};

