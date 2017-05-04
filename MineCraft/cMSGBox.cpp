#include "stdafx.h"
#include "cMSGBox.h"
#include "cText_2D.h"

cMSGBox::cMSGBox() : m_pText(NULL)
{
}


cMSGBox::~cMSGBox()
{
	SAFE_DELETE(m_pText);
}

void cMSGBox::Setup(D3DXVECTOR2 leftTop, D3DXVECTOR2 rightBottom, int size, D3DXCOLOR color)
{
	m_vLeftTop = leftTop;
	m_vRightBottom = rightBottom;
	m_size = size;
	m_color = color;
	m_pText = new cText_2D;
}

void cMSGBox::RegisterMSG(int key, string msg)
{
	if (m_mapMSG.find(key) == m_mapMSG.end())
	{
		m_mapMSG[key] = msg;
	}
}

void cMSGBox::EraseMSG(int key)
{
	if (m_mapMSG.find(key) != m_mapMSG.end())
	{
		m_mapMSG.erase(key);
	}
}

void cMSGBox::Render(int key)
{
	RECT rc = { m_vLeftTop.x, m_vLeftTop.y, m_vRightBottom.x, m_vRightBottom.y };
	m_pText->Create(rc, m_mapMSG[key], m_size, m_color);
	m_pText->Render();
}