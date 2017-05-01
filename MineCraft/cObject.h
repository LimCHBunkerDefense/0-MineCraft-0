#pragma once
#include "cCubePNT.h"
class cObject :
	public cCubePNT
{
	D3DXVECTOR3		m_vLocalPos;
	D3DXMATRIXA16	m_matLocalTM;
public:
	cObject();
	cObject(D3DXVECTOR3 pos);
	~cObject();
	D3DXVECTOR3 GetPosition() { return m_vLocalPos; }
};

