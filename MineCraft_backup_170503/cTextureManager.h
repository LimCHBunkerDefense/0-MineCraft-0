#pragma once

#define g_pTextureManager cTextureManager::GetInstance()
class cTextureManager
{
	//public:
	//	cTextureManager();
	//	~cTextureManager();

private:
	SINGLETONE(cTextureManager);

	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(string& sFullPath);
	void Destroy();
	// >>:�ؽ��� �ε�����ǥ
	void TextureIdexPos();
	// <<:
};

