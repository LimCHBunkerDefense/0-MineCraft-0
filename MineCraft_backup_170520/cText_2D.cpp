#include "stdafx.h"
#include "cText_2D.h"


cText_2D::cText_2D()
{
	m_Font = NULL;
	m_color = D3DCOLOR_XRGB(0, 0, 0);
}


cText_2D::~cText_2D()
{

}

void cText_2D::Create(RECT rect, string message, int size, D3DXCOLOR color)
{
	if (m_Font) Clear();

	m_Rect = rect;
	m_message = message;
	m_size = size;
	m_color = color;
	D3DXCreateFont(g_pD3DDevice, m_size, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, TEXT("Arial"), &m_Font);
}
void cText_2D::Delete(string message)
{

}

void cText_2D::Clear()
{
	m_Font->Release();
	m_Font = NULL;
}

void cText_2D::Render()
{
	if(m_Font)m_Font->DrawTextA(NULL, m_message.c_str(), -1, &m_Rect, DT_LEFT, m_color);
}


