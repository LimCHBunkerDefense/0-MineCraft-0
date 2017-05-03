#pragma once
class cText
{
	LPCWSTR				m_text;
	D3DXMATRIXA16		m_matT;
	D3DXMATRIXA16		m_matS;
	D3DXMATRIXA16		m_matR;
	D3DXCOLOR			m_color;

	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMtl;
public:
	cText();
	cText(LPCWSTR text, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rotation = D3DXVECTOR3(0,0,0),  D3DXCOLOR color = D3DCOLOR_XRGB(0,0,0,0));
	~cText();

	void Render();
};

