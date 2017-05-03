#pragma once
class cSurface
{
public:
	cSurface();
	~cSurface();

	void Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 v4, LPCWSTR imagePath);
	void Render();
	void UpdateLocation(D3DXVECTOR3 vPosition);
	void SetisThisLogo();
	void logoScaling();
	void SetUI(float width, float height);

	//>>:����������
	float IMG_SetScale(float scale);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	vector<ST_PNT_VERTEX>	m_vecVertex;

	float       m_imgScale; //������ ����
	bool        m_isBiglogoScale;
	bool        m_isThisLogo;
};

