#include "stdafx.h"
#include "cObject.h"


cObject::cObject():m_vLocalPos(0,0,0)
{
	cCubePNT::Setup();
	D3DXMatrixIdentity(&m_matLocalTM);
}

cObject::cObject(D3DXVECTOR3 pos)
{
	cCubePNT::Setup();
	m_vLocalPos = pos;
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y + 0.5f, m_vLocalPos.z);
	for (int i = 0; i < m_vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matT);
}


cObject::~cObject()
{
}

void cObject::SetDirtTexture()
{
	

	m_vecVertex[30].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[31].t = D3DXVECTOR2(0, 0.75);
	m_vecVertex[32].t = D3DXVECTOR2(0.25, 0.75);
	m_vecVertex[33].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[34].t = D3DXVECTOR2(0.25, 0.75);
	m_vecVertex[35].t = D3DXVECTOR2(0.25, 0.5);
}

void cObject::Render()
{
	cCubePNT::Render();
}
