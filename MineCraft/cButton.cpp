#include "stdafx.h"
#include "cButton.h"
#include "cText_2D.h"


cButton::cButton() : m_pText(NULL)
{
	SOUND->LoadFile("click", "Sound/click.mp3", false);
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

	m_pText = new cText_2D;

	m_vLeftTop.x = VIEW_WIDTH * 0.5 + (m_vecVertex[0].p.x);
	m_vLeftTop.y = VIEW_HEIGHT - m_vecVertex[1].p.y;
	m_vRightBottom.x = VIEW_WIDTH * 0.5 + m_vecVertex[2].p.x;
	m_vRightBottom.y = VIEW_HEIGHT - m_vecVertex[5].p.y;

}

void cButton::Update()
{
	if (IsCollided())
	{
		int r = 150;
		int g = 150;
		int b = 200;

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

	if (IsPressed())
	{
		for (int i = 0; i < m_vecVertex_Top.size(); i++)
		{
			m_vecVertex_Top[i].c = D3DCOLOR_XRGB(50, 50, 50, 1);
		}
		for (int i = 0; i < m_vecVertex_Bottom.size(); i++)
		{
			m_vecVertex_Bottom[i].c = D3DCOLOR_XRGB(255, 255, 255, 1);
		}

		int r = m_color.r * 255 * 0.6;
		int g = m_color.g * 255 * 0.6;
		int b = m_color.b * 255 * 0.6;
		for (int i = 0; i < m_vecVertex.size(); i++)
		{	
			m_vecVertex[i].c = D3DCOLOR_XRGB(r, g, b, 1);
		}

		if (m_pText) m_pText->SetColor(D3DCOLOR_XRGB(255, 255, 255, 1));
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
		if (m_pText) m_pText->SetColor(D3DCOLOR_XRGB(0,0,0, 1));
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

	if(m_pText) m_pText->Render();

	g_pD3DDevice->SetTexture(0, NULL);


}

void cButton::SetText(string text, RECT rect, int fontSize,  D3DXCOLOR fontColor)
{
	m_pText->Create(rect, text, fontSize, fontColor);
}

bool cButton::IsCollided()
{
	POINT pos = INPUT->GetMousePos();
	D3DXVECTOR2 mousePos = D3DXVECTOR2(pos.x, pos.y);

	if (mousePos.x >= m_vLeftTop.x &&
		mousePos.x < m_vRightBottom.x &&
		mousePos.y >= m_vLeftTop.y &&
		mousePos.y < m_vRightBottom.y)	return true;
	return false;
}

bool cButton::IsPressed()
{
	if (INPUT->IsMousePress(MOUSE_LEFT))
	{
		POINT pos = INPUT->GetMousePos();
		D3DXVECTOR2 mousePos = D3DXVECTOR2(pos.x, pos.y);

		if (mousePos.x >= m_vLeftTop.x &&
			mousePos.x < m_vRightBottom.x &&
			mousePos.y >= m_vLeftTop.y &&
			mousePos.y < m_vRightBottom.y) return true;		
	}
	return false;	
}

bool cButton::IsClicked()
{
	if (INPUT->IsMouseUp(MOUSE_LEFT))
	{
		POINT pos = INPUT->GetMousePos();
		D3DXVECTOR2 mousePos = D3DXVECTOR2(pos.x, pos.y);

		if (mousePos.x >= m_vLeftTop.x &&
			mousePos.x < m_vRightBottom.x &&
			mousePos.y >= m_vLeftTop.y &&
			mousePos.y < m_vRightBottom.y)
		{
			SOUND->Play("click");
			return true;
		}
	}
	return false;
}

D3DXVECTOR2 cButton::LeftTop()
{
	return m_vLeftTop;
}
D3DXVECTOR2 cButton::RightBottom()
{
	return m_vRightBottom;
}