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
	m_color = color;
	/*
	v1	v2
	v0	v3
	*/

	// 버튼을 위한 vertex
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

	// 버튼의 윤곽선 좌측+상단을 위한vertex
	ver.c = D3DCOLOR_XRGB(255,255,255,1);

	ver.p = v2 + D3DXVECTOR3(-5.0f, 0.0f, 0.0f);				// >> 상단 시작
	m_vecVertex_Top.push_back(ver);

	ver.p = v2 + D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v2 + D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v3;
	m_vecVertex_Top.push_back(ver);

	ver.p = v3;
	m_vecVertex_Top.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);								//	<< 상단 종료

	ver.p = v1 + D3DXVECTOR3(-5.0f, 0.0f, 0.0f);				// >> 좌측 시작
	m_vecVertex_Top.push_back(ver);

	ver.p = v2 + D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v2 + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v1 + D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v2 + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v1;
	m_vecVertex_Top.push_back(ver);

	ver.p = v1 + D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v1 + D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
	m_vecVertex_Top.push_back(ver);

	ver.p = v1;
	m_vecVertex_Top.push_back(ver);								// << 좌측 종료

	// 벼튼의 윤곽선 우측+하단을 위한 vertex

	ver.c = D3DCOLOR_XRGB(50, 50, 50, 1);

	ver.p = v1 + D3DXVECTOR3(-5.0f, -5.0f, 0.0f);				// >> 하단 시작
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v1;
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v1 + D3DXVECTOR3(0.0f, -5.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v1 + D3DXVECTOR3(0.0f, -5.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v1;
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v4 + D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v1 + D3DXVECTOR3(0.0f, -5.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v4 + D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v4 + D3DXVECTOR3(5.0f, -5.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);							// << 하단 종료

	ver.p = v3;													// >> 좌측 시작
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v4 + D3DXVECTOR3(0.0f, -5.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v3;
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v4;
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v3 + D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);

	ver.p = v4 + D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	m_vecVertex_Bottom.push_back(ver);
}

void cButton::Update()
{
	if (IsCollided())
	{
		for (int i = 0; i < m_vecVertex_Top.size(); i++)
		{
			m_vecVertex_Top[i].c = D3DCOLOR_XRGB(50, 50, 50, 1);
		}
		for (int i = 0; i < m_vecVertex_Bottom.size(); i++)
		{
			m_vecVertex_Bottom[i].c = D3DCOLOR_XRGB(255, 255, 255, 1);
		}
	}
	else
	{
		for (int i = 0; i < m_vecVertex_Top.size(); i++)
		{
			m_vecVertex_Top[i].c = D3DCOLOR_XRGB(255, 255, 255, 1);
		}
		for (int i = 0; i < m_vecVertex_Bottom.size(); i++)
		{
			m_vecVertex_Bottom[i].c = D3DCOLOR_XRGB(50, 50, 50, 1);
		}
	}

	if(IsPressed())
	{
		int r = 255 * m_color.r * 0.6;
		int g = 255 * m_color.g * 0.6;
		int b = 255 * m_color.b * 0.6;

		for (int i = 0; i < m_vecVertex.size(); i++)
		{
			m_vecVertex[i].c = D3DCOLOR_XRGB(r, g, b, 1);
		}
	}
	else
	{
		for (int i = 0; i < m_vecVertex.size(); i++)
		{
			m_vecVertex[i].c = m_color;
		}
	}
}

void cButton::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);


	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Top.size() / 3,
		&m_vecVertex_Top[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Bottom.size() / 3,
		&m_vecVertex_Bottom[0],
		sizeof(ST_PC_VERTEX));

	DrawText_Button();

}

void cButton::SetText(string text, int size, D3DXCOLOR color)
{
	m_text = text;
	m_fontColor = color;
	m_fontSize = size;
}

void cButton::DrawText_Button()
{
	HDC hdc = CreateCompatibleDC(NULL);

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 25;
	lf.lfWidth = 12;
	lf.lfWeight = 500;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfCharSet = DEFAULT_CHARSET;
	wcscpy_s(lf.lfFaceName, _countof(lf.lfFaceName), _T("Arial"));

	HFONT hFont;
	HFONT hFontOld;
	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);

	ID3DXMesh* Text = 0;

	bool aaa = D3DXCreateText(g_pD3DDevice, hdc, _T("P L A Y"), 0.001f, 0.4f, &Text, 0, 0);
	
	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, 0, 2, 0);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	Text->DrawSubset(0);
	//Text->Release();

}

bool cButton::IsCollided()
{
	POINT pos = INPUT->GetMousePos();
	D3DXVECTOR2 mousePos = D3DXVECTOR2(pos.x, pos.y);

	D3DXVECTOR2 leftTop, rightBottom;
	leftTop.x = VIEW_WIDTH * 0.5 + (m_vecVertex[0].p.x);
	leftTop.y = VIEW_HEIGHT - m_vecVertex[1].p.y;
	rightBottom.x = VIEW_WIDTH * 0.5 + m_vecVertex[2].p.x;
	rightBottom.y = VIEW_HEIGHT - m_vecVertex[5].p.y;

	if (mousePos.x >= leftTop.x &&
		mousePos.x < rightBottom.x &&
		mousePos.y >= leftTop.y &&
		mousePos.y < rightBottom.y) return true;
	return false;
}

bool cButton::IsPressed()
{
	if (INPUT->IsMousePress(MOUSE_LEFT))
	{
		POINT pos = INPUT->GetMousePos();
		D3DXVECTOR2 mousePos = D3DXVECTOR2(pos.x, pos.y);

		D3DXVECTOR2 leftTop, rightBottom;
		leftTop.x = VIEW_WIDTH * 0.5 - fabs(m_vecVertex[0].p.x);
		leftTop.y = VIEW_HEIGHT - m_vecVertex[1].p.y;
		rightBottom.x = VIEW_WIDTH * 0.5 + m_vecVertex[2].p.x;
		rightBottom.y = VIEW_HEIGHT - m_vecVertex[5].p.y;

		if (mousePos.x >= leftTop.x &&
			mousePos.x < rightBottom.x &&
			mousePos.y >= leftTop.y &&
			mousePos.y < rightBottom.y) return true;		
	}
	return false;	
}

bool cButton::IsClicked()
{
	if (INPUT->IsMouseUp(MOUSE_LEFT))
	{
		POINT pos = INPUT->GetMousePos();
		D3DXVECTOR2 mousePos = D3DXVECTOR2(pos.x, pos.y);

		D3DXVECTOR2 leftTop, rightBottom;
		leftTop.x = VIEW_WIDTH * 0.5 - fabs(m_vecVertex[0].p.x);
		leftTop.y = VIEW_HEIGHT - m_vecVertex[1].p.y;
		rightBottom.x = VIEW_WIDTH * 0.5 + m_vecVertex[2].p.x;
		rightBottom.y = VIEW_HEIGHT - m_vecVertex[5].p.y;

		if (mousePos.x >= leftTop.x &&
			mousePos.x < rightBottom.x &&
			mousePos.y >= leftTop.y &&
			mousePos.y < rightBottom.y) return true;
	}
	return false;
}
