#include "stdafx.h"
#include "cText.h"


cText::cText()
{
}

cText::cText(LPCWSTR text, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rotation, D3DXCOLOR color) :
	m_color(color), m_pTexture(NULL)
{
	m_text = text;
	D3DXMatrixIdentity(&m_matT);
	D3DXMatrixTranslation(&m_matT, pos.x, pos.y, pos.z);

	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixScaling(&m_matS, size.x, size.y, size.z);

	D3DXMATRIXA16 matRX, matRY, matRZ;
	D3DXMatrixIdentity(&matRX);
	D3DXMatrixIdentity(&matRY);
	D3DXMatrixIdentity(&matRZ);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixRotationX(&matRX, rotation.x);
	D3DXMatrixRotationY(&matRY, rotation.y);
	D3DXMatrixRotationZ(&matRZ, rotation.z);
	m_matR = matRX * matRY * matRZ;
}

cText::~cText()
{
	SAFE_DELETE(m_pTexture);
}

void cText::Render()
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

	bool aaa = D3DXCreateText(g_pD3DDevice, hdc, (m_text), 0.001f, 0.4f, &Text, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	mat = m_matS * m_matR * m_matT;

	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	Text->DrawSubset(0);


}