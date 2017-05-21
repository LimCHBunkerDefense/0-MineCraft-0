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
	map<float, D3DXVECTOR2> m_TextureIndex;
	map<int, LPDIRECT3DTEXTURE9> m_mapSkin;
public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(string& sFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(int key);
	void Destroy();
	// >>:ÅØ½ºÃÄ ÀÎµ¦½ºÁÂÇ¥
	void SetupIndex();
	void SetNormal(OBJECT_NAME name, vector<ST_PNT_VERTEX>& vecVertex);
	// <<:
};

