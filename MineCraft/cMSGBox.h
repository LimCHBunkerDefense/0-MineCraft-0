#pragma once

class cText_2D;

class cMSGBox
{
	map<int, string>		m_mapMSG;
	D3DXVECTOR2				m_vLeftTop;
	D3DXVECTOR2				m_vRightBottom;
	cText_2D*				m_pText;
	int						m_size;
	D3DXCOLOR				m_color;

public:
	cMSGBox();
	~cMSGBox();

	void Setup(D3DXVECTOR2 leftTop, D3DXVECTOR2 rightBottom, int size, D3DXCOLOR color);
	void RegisterMSG(int key, string msg);
	void EraseMSG(int key);
	void Render(int key);
	void SetColor(D3DXCOLOR color) { m_color = color; }
	void SetSize(int size) { m_size = size; }
};

