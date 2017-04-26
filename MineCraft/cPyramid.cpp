#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
}


cPyramid::~cPyramid()
{
}

void cPyramid::Setup(D3DXCOLOR c, D3DXMATRIXA16& mat)
{
	/// >> : 13.
	{	/// : material ����
		ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
		m_stMtl.Ambient = c;
		m_stMtl.Diffuse = c;
		m_stMtl.Specular = c;
	}
	/// << : 13. 


	m_matR = mat;

	///ST_PC_VERTEX v;	// << : 13.
	///v.c = c;	// << : 
	ST_PN_VERTEX v;	// << : 13.


	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);

	// >> : 
	for (int i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v01 = m_vecVertex[i + 1].p - m_vecVertex[i].p;
		D3DXVECTOR3 v02 = m_vecVertex[i + 2].p - m_vecVertex[i].p;
		D3DXVECTOR3 n;

		D3DXVec3Cross(&n, &v01, &v02);
		D3DXVec3Normalize(&n, &n);

		m_vecVertex[i].n = n;
		m_vecVertex[i + 1].n = n;
		m_vecVertex[i + 2].n = n;
	}
	/// << : 
}

void cPyramid::Render()
{
	D3DXMATRIXA16 matWorld, matS;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);

	matWorld = matS * m_matR;

	/// >> :
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);	// << : 13. 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));
}