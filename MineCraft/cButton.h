#pragma once

class cText;
class cText_2D;

class cButton
{
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<ST_PC_VERTEX>	m_vecVertex_Top;
	vector<ST_PC_VERTEX>	m_vecVertex_Bottom;
	D3DXCOLOR				m_color;
	cText_2D*				m_pText;
	D3DXVECTOR2				m_vLeftTop;
	D3DXVECTOR2				m_vRightBottom;

public:
	cButton();
	~cButton(); 

	void Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 v4, D3DXCOLOR color);
	void Update();
	void Render();

	void SetText(string text, RECT rect, int fontSize, D3DXCOLOR fontColor = D3DCOLOR_XRGB(0,0,0,0));
	bool IsCollided();
	bool IsPressed();
	bool IsClicked();
	D3DXVECTOR2 LeftTop();
	D3DXVECTOR2 RightBottom();
};

