#include "stdafx.h"
#include "cSurface.h"


cSurface::cSurface() : m_pTexture(NULL)
{
}


cSurface::~cSurface()
{
	SAFE_RELEASE(m_pTexture);
}

void cSurface::Setup(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, LPCWSTR imagePath)
{
	/*
	v1	v2
	v0	v3
	*/
	//D3DXCreateTextureFromFile(g_pD3DDevice, imagePath, &m_pTexture);

	ST_PNT_VERTEX ver;

	ver.p = D3DXVECTOR3(x1, y1, z1);
	ver.t = D3DXVECTOR2(0.0f, 1.0f);
	m_vecVertex.push_back(ver);

	ver.p = D3DXVECTOR3(x2, y2, z2);
	ver.t = D3DXVECTOR2(0.0f, 0.0f);
	m_vecVertex.push_back(ver);

	ver.p = D3DXVECTOR3(x3, y3, z3);
	ver.t = D3DXVECTOR2(1.0f, 0.0f);
	m_vecVertex.push_back(ver);

	ver.p = D3DXVECTOR3(x1, y1, z1);
	ver.t = D3DXVECTOR2(0.0f, 1.0f);
	m_vecVertex.push_back(ver);

	ver.p = D3DXVECTOR3(x3, y3, z3);
	ver.t = D3DXVECTOR2(1.0f, 0.0f);
	m_vecVertex.push_back(ver);

	ver.p = D3DXVECTOR3(x4, y4, z4);
	ver.t = D3DXVECTOR2(1.0f, 1.0f);
	m_vecVertex.push_back(ver);

	D3DXVECTOR3 u, v, n;
	for (int i = 0; i < 6; i += 3)
	{
		u = m_vecVertex[i + 1].p - m_vecVertex[i].p;
		v = m_vecVertex[i + 2].p - m_vecVertex[i].p;

		D3DXVec3Cross(&n, &u, &v);
		D3DXVec3Normalize(&n, &n);
		m_vecVertex[i + 0].n = n;
		m_vecVertex[i + 1].n = n;
		m_vecVertex[i + 2].n = n;
	}
}

void cSurface::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
}
