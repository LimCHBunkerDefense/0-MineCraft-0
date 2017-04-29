#pragma once
class cSurface
{
public:
	cSurface();
	~cSurface();

	void Setup(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, LPCWSTR imagePath);
	void Render();


private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	vector<ST_PNT_VERTEX>	m_vecVertex;
};

