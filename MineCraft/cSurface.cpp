#include "stdafx.h"
#include "cSurface.h"


cSurface::cSurface() : m_pTexture(NULL)
{
}


cSurface::~cSurface()
{
	SAFE_RELEASE(m_pTexture);
}

void cSurface::Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 v4, LPCWSTR imagePath)
{
	/*
	v1	v2
	v0	v3
	*/
	D3DXCreateTextureFromFile(g_pD3DDevice, imagePath, &m_pTexture);

	ST_PNT_VERTEX ver;

	ver.p = v1;
	ver.t = D3DXVECTOR2(0.0f, 1.0f);
	m_vecVertex.push_back(ver);

	ver.p = v2;
	ver.t = D3DXVECTOR2(0.0f, 0.0f);
	m_vecVertex.push_back(ver);

	ver.p = v3;
	ver.t = D3DXVECTOR2(1.0f, 0.0f);
	m_vecVertex.push_back(ver);

	ver.p = v1;
	ver.t = D3DXVECTOR2(0.0f, 1.0f);
	m_vecVertex.push_back(ver);

	ver.p = v3;
	ver.t = D3DXVECTOR2(1.0f, 0.0f);
	m_vecVertex.push_back(ver);

	ver.p = v4;
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

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
}

void cSurface::UpdateLocation(D3DXVECTOR3 vPosition)
{
	D3DXVECTOR3 v1 = vPosition + D3DXVECTOR3(-0.5f, 0.0f, -0.5f);
	D3DXVECTOR3 v2 = vPosition + D3DXVECTOR3(-0.5f, 0.0f, 0.5f);
	D3DXVECTOR3 v3 = vPosition + D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	D3DXVECTOR3 v4 = vPosition + D3DXVECTOR3(0.5f, 0.0f, -0.5f);

	m_vecVertex[0].p = v1;
	m_vecVertex[1].p = v2;
	m_vecVertex[2].p = v3;
	m_vecVertex[3].p = v1;
	m_vecVertex[4].p = v3;
	m_vecVertex[5].p = v4;
}
