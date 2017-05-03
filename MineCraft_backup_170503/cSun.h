#pragma once
#include "cCubePNT.h"

class cSun : public cCubePNT
{
public:
	cSun();
	~cSun();

public:
	cCubePNT*			m_pSun;

	D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMtl;

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual D3DXVECTOR3& GetPosition();
	void Set_Light();
	void Set_Material();
	void Set_Texture();
};

