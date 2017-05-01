#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
{
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
