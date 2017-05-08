#include "stdafx.h"
#include "cRightArm.h"


cRightArm::cRightArm()
{
}


cRightArm::~cRightArm()
{
}

void cRightArm::Setup()
{
	cCubeNode::Setup();

	{
		// µÞ¸é
		m_vecVertex[0].t = D3DXVECTOR2((float)13 / 16, 1);
		m_vecVertex[1].t = D3DXVECTOR2((float)13 / 16, (float)5 / 8);
		m_vecVertex[2].t = D3DXVECTOR2((float)14 / 16, (float)5 / 8);

		m_vecVertex[3].t = D3DXVECTOR2((float)13 / 16, 1);
		m_vecVertex[4].t = D3DXVECTOR2((float)14 / 16, (float)5 / 8);
		m_vecVertex[5].t = D3DXVECTOR2((float)14 / 16, 1);

		// ¾Õ¸é
		m_vecVertex[6].t = D3DXVECTOR2((float)12 / 16, 1);
		m_vecVertex[7].t = D3DXVECTOR2((float)11 / 16, (float)5 / 8);
		m_vecVertex[8].t = D3DXVECTOR2((float)12 / 16, (float)5 / 8);

		m_vecVertex[9].t = D3DXVECTOR2((float)12 / 16, 1);
		m_vecVertex[10].t = D3DXVECTOR2((float)11 / 16, 1);
		m_vecVertex[11].t = D3DXVECTOR2((float)11 / 16, (float)5 / 8);

		// ¿ÞÂÊ
		m_vecVertex[12].t = D3DXVECTOR2((float)13 / 16, 1);
		m_vecVertex[13].t = D3DXVECTOR2((float)13 / 16, (float)5 / 8);
		m_vecVertex[14].t = D3DXVECTOR2((float)12 / 16, (float)5 / 8);

		m_vecVertex[15].t = D3DXVECTOR2((float)13 / 16, 1);
		m_vecVertex[16].t = D3DXVECTOR2((float)12 / 16, (float)5 / 8);
		m_vecVertex[17].t = D3DXVECTOR2((float)12 / 16, 1);

		// ¿À¸¥ÂÊ
		m_vecVertex[18].t = D3DXVECTOR2((float)11 / 16, 1);
		m_vecVertex[19].t = D3DXVECTOR2((float)11 / 16, (float)5 / 8);
		m_vecVertex[20].t = D3DXVECTOR2((float)10 / 16, (float)5 / 8);

		m_vecVertex[21].t = D3DXVECTOR2((float)11 / 16, 1);
		m_vecVertex[22].t = D3DXVECTOR2((float)10 / 16, (float)5 / 8);
		m_vecVertex[23].t = D3DXVECTOR2((float)10 / 16, 1);

		// À­¸é
		m_vecVertex[24].t = D3DXVECTOR2((float)12 / 16, (float)5 / 8);
		m_vecVertex[25].t = D3DXVECTOR2((float)12 / 16, 0.5f);
		m_vecVertex[26].t = D3DXVECTOR2((float)11 / 16, 0.5f);

		m_vecVertex[27].t = D3DXVECTOR2((float)12 / 16, (float)5 / 8);
		m_vecVertex[28].t = D3DXVECTOR2((float)11 / 16, 0.5f);
		m_vecVertex[29].t = D3DXVECTOR2((float)11 / 16, (float)5 / 8);

		// ¾Æ·§¸é
		m_vecVertex[30].t = D3DXVECTOR2((float)13 / 16, 0.5f);
		m_vecVertex[31].t = D3DXVECTOR2((float)13 / 16, (float)5 / 8);
		m_vecVertex[32].t = D3DXVECTOR2((float)12 / 16, (float)5 / 8);

		m_vecVertex[33].t = D3DXVECTOR2((float)13 / 16, 0.5f);
		m_vecVertex[34].t = D3DXVECTOR2((float)12 / 16, (float)5 / 8);
		m_vecVertex[35].t = D3DXVECTOR2((float)12 / 16, 0.5f);
	}
	
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f * m_fScale, 0.6f * m_fScale, 0.2f * m_fScale);
	D3DXMatrixTranslation(&matT, 0.3f * m_fScale, -0.3f * m_fScale, 0.0f * m_fScale);
	mat = matS*matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPos.y = 1.2f * m_fScale;
}
