#pragma once
class cSurface
{
public:
	cSurface();
	~cSurface();

	void Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 v4, LPCWSTR imagePath, bool IsLightOn);
	void Render();
	void UpdateLocation(D3DXVECTOR3 vPosition);
	void SetisThisLogo();
	void logoScaling();
	void SetUI(float width, float height);
	void SetMaterial(D3DXVECTOR4 ambient, D3DXVECTOR4 diffuse, D3DXVECTOR4 specular, D3DXVECTOR4 emissive, float power = 1.0f);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DMATERIAL9			m_stMtl;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	bool					m_isLightOn;

	float       m_logoScale;
	bool        m_isBiglogoScale;
	bool        m_isThisLogo;
};

