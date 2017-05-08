#include "stdafx.h"
#include "cHead.h"


cHead::cHead()
{
}


cHead::~cHead()
{
}

void cHead::Setup()
{
	cCubeNode::Setup();

	{
		// µÞ¸é
		m_vecVertex[0].t = D3DXVECTOR2(0.375f, 0.5f);
		m_vecVertex[1].t = D3DXVECTOR2(0.375f, 0.25f);
		m_vecVertex[2].t = D3DXVECTOR2(0.5f, 0.25f);

		m_vecVertex[3].t = D3DXVECTOR2(0.375f, 0.5f);
		m_vecVertex[4].t = D3DXVECTOR2(0.5f, 0.25f);
		m_vecVertex[5].t = D3DXVECTOR2(0.5f, 0.5f);

		// ¾Õ¸é
		m_vecVertex[6].t = D3DXVECTOR2(0.125f, 0.5f);
		m_vecVertex[7].t = D3DXVECTOR2(0.25f, 0.25f);
		m_vecVertex[8].t = D3DXVECTOR2(0.125f, 0.25f);

		m_vecVertex[9].t = D3DXVECTOR2(0.125f, 0.5f);
		m_vecVertex[10].t = D3DXVECTOR2(0.25f, 0.5f);
		m_vecVertex[11].t = D3DXVECTOR2(0.25f, 0.25f);

		// ¿ÞÂÊ
		m_vecVertex[12].t = D3DXVECTOR2(0.25f, 0.5f);
		m_vecVertex[13].t = D3DXVECTOR2(0.25f, 0.25f);
		m_vecVertex[14].t = D3DXVECTOR2(0.375f, 0.25f);

		m_vecVertex[15].t = D3DXVECTOR2(0.25f, 0.5f);
		m_vecVertex[16].t = D3DXVECTOR2(0.375f, 0.25f);
		m_vecVertex[17].t = D3DXVECTOR2(0.375f, 0.5f);

		// ¿À¸¥ÂÊ
		m_vecVertex[18].t = D3DXVECTOR2(0, 0.5f);
		m_vecVertex[19].t = D3DXVECTOR2(0, 0.25f);
		m_vecVertex[20].t = D3DXVECTOR2(0.125f, 0.25f);

		m_vecVertex[21].t = D3DXVECTOR2(0, 0.5f);
		m_vecVertex[22].t = D3DXVECTOR2(0.125f, 0.25f);
		m_vecVertex[23].t = D3DXVECTOR2(0.125f, 0.5f);

		// À­¸é
		m_vecVertex[24].t = D3DXVECTOR2(0.25f, 0);
		m_vecVertex[25].t = D3DXVECTOR2(0.25f, 0.25f);
		m_vecVertex[26].t = D3DXVECTOR2(0.125f, 0.25f);

		m_vecVertex[27].t = D3DXVECTOR2(0.25f, 0);
		m_vecVertex[28].t = D3DXVECTOR2(0.125f, 0.25f);
		m_vecVertex[29].t = D3DXVECTOR2(0.125f, 0);

		// ¾Æ·§¸é
		m_vecVertex[30].t = D3DXVECTOR2(0.25f, 0);
		m_vecVertex[31].t = D3DXVECTOR2(0.25f, 0.25f);
		m_vecVertex[32].t = D3DXVECTOR2(0.375f, 0.25f);

		m_vecVertex[33].t = D3DXVECTOR2(0.25f, 0);
		m_vecVertex[34].t = D3DXVECTOR2(0.375f, 0.25f);
		m_vecVertex[35].t = D3DXVECTOR2(0.375f, 0);
	}

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f * m_fScale, 0.4f * m_fScale, 0.4f * m_fScale);
	D3DXMatrixTranslation(&matT, 0.0f * m_fScale, 0.0f * m_fScale, 0.0f * m_fScale);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPos.y = 1.4 * m_fScale;
}
