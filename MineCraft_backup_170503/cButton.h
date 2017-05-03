#pragma once

class cText;

class cButton
{
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<ST_PC_VERTEX>	m_vecVertex_Top;
	vector<ST_PC_VERTEX>	m_vecVertex_Bottom;
	D3DXCOLOR				m_color;

	cText*					m_text;

public:
	cButton();
	~cButton(); 

	void Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 v4, D3DXCOLOR color);
	void Update();
	void Render();

	void SetText(LPCWSTR text, D3DXVECTOR3 fontPos, D3DXVECTOR3 fontSize, D3DXVECTOR3 m_fontRot = D3DXVECTOR3(0,0,0), D3DXCOLOR fontColor = D3DCOLOR_XRGB(0,0,0,0));
	bool IsCollided();
	bool IsPressed();
	bool IsClicked();
};

