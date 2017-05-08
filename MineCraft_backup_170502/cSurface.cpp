#include "stdafx.h"
#include "cSurface.h"


cSurface::cSurface() : m_pTexture(NULL),
m_logoScale(1.0f),
m_isBiglogoScale(false),
m_isThisLogo(false)
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
	if (m_isThisLogo == true)logoScaling();
	D3DXMATRIXA16 matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, m_logoScale, m_logoScale, m_logoScale);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matS);
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	mat = matS*mat;
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

	g_pD3DDevice->SetTexture(0, NULL);
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

void cSurface::SetisThisLogo()
{
	m_isThisLogo = true;
}

void cSurface::logoScaling()
{
	if (m_isBiglogoScale == false)m_logoScale += 0.005f;
	if (m_isBiglogoScale == true)m_logoScale -= 0.005f;
	if (m_logoScale >= 1.05f)m_isBiglogoScale = true;
	else if (m_logoScale <= 0.95f)m_isBiglogoScale = false;
}

void cSurface::SetUI(float width, float height)
{
	m_vecVertex[0].t = D3DXVECTOR2(0.0f, height);		// v1
	m_vecVertex[1].t = D3DXVECTOR2(0.0f, 0.0f);		// v2
	m_vecVertex[2].t = D3DXVECTOR2(width, 0.0f);		// v3
	m_vecVertex[3].t = D3DXVECTOR2(0.0f, height);		// v1
	m_vecVertex[4].t = D3DXVECTOR2(width, 0.0f);		// v3
	m_vecVertex[5].t = D3DXVECTOR2(width, height);		// v4
}