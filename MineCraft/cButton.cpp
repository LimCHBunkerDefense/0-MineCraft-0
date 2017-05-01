#include "stdafx.h"
#include "cButton.h"


cButton::cButton()
{
}


cButton::~cButton()
{
}

void cButton::Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 v4, D3DXCOLOR color)
{
	/*
	v1	v2
	v0	v3
	*/
	ST_PC_VERTEX ver;

	ver.c = color;

	ver.p = v1;
	m_vecVertex.push_back(ver);

	ver.p = v2;
	m_vecVertex.push_back(ver);

	ver.p = v3;
	m_vecVertex.push_back(ver);

	ver.p = v1;
	m_vecVertex.push_back(ver);

	ver.p = v3;
	m_vecVertex.push_back(ver);

	ver.p = v4;
	m_vecVertex.push_back(ver);
}

void cButton::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(g_hWnd, &ps);
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	
	PatBlt(hdc, rc.bottom, rc.top, rc.right, rc.bottom, WHITENESS);
	
	MoveToEx(hdc, m_vecVertex[0].p.x - 0.1f, m_vecVertex[0].p.y - 0.1f, NULL);
	LineTo(hdc, m_vecVertex[1].p.x - 0.1f, m_vecVertex[1].p.y + 0.1f);
	LineTo(hdc, m_vecVertex[2].p.x + 0.1f, m_vecVertex[2].p.y + 0.1f);
	
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdc, 0, 0, SRCCOPY);
	
	EndPaint(g_hWnd, &ps);
	

}