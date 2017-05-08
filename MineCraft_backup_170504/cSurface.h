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

	// >> : 창영 수정부분
	bool GetIsLightOn() { return m_isLightOn; }
	void SetIsLightOn(bool isLightOn) { m_isLightOn = isLightOn; }
	void SetUI(float width, float height);
	void SetMaterial(D3DXVECTOR4 ambient, D3DXVECTOR4 diffuse, D3DXVECTOR4 specular, D3DXVECTOR4 emissive, float power = 1.0f);

	//>>:스케일조절
	float IMG_SetScale(float scale);

	vector<ST_PNT_VERTEX> GetVerTex();
private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DMATERIAL9			m_stMtl;
	vector<ST_PNT_VERTEX>	m_vecVertex;
	bool					m_isLightOn;

	float       m_imgScale; //변수명 변경
	bool        m_isBiglogoScale;
	bool        m_isThisLogo;
};

