#pragma once
class cButton
{
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<ST_PC_VERTEX>	m_vecVertex_Top;
	vector<ST_PC_VERTEX>	m_vecVertex_Bottom;
	D3DXCOLOR				m_color;

public:
	cButton();
	~cButton(); 

	void Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 v4, D3DXCOLOR color);
	void Update();
	void Render();

	bool IsCollided();
	bool IsPressed();
	bool IsClicked();
};

