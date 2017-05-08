#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("image/Dirt.png"), &m_mapTexture["Dirt"]);
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("image/Texture/Texture00.png"), &m_mapTexture["Texture00"]); // 경로 텍스쳐폴더 및 이름변경
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("image/Skin/batman.png"), &m_mapSkin[SKIN_BATMAN]);
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("image/Skin/CaptainAmerica.png"), &m_mapSkin[SKIN_CAPTAIN]);
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("image/Skin/Ironman.png"), &m_mapSkin[SKIN_IRON]);
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("image/Skin/Spiderman.png"), &m_mapSkin[SKIN_SPIDER]);
	SetupIndex();
}


cTextureManager::~cTextureManager()
{
	///*for (map<string, LPDIRECT3DTEXTURE9>::iterator it = m_mapTexture.begin(); it != m_mapTexture.end(); it++)
	//{
	//	
	//}*/
	m_mapTexture.clear();
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char* keyName)
{
	if (m_mapTexture.find(keyName) == m_mapTexture.end())
	{
		string szFilePath ="image/"+ (string)keyName + ".png";  // 텍스쳐 이미지 기본경로.
		D3DXCreateTextureFromFile(g_pD3DDevice, (LPCWSTR)((char*)szFilePath.c_str()), &m_mapTexture[keyName]);
	}
	return m_mapTexture[keyName];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(string & keyName)
{
	return GetTexture((char*)keyName.c_str());
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(int key)
{
	if (!(m_mapSkin.find(key) == m_mapSkin.end()))
	{
		return m_mapSkin[key];
	}
	return NULL;
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}


void cTextureManager::SetupIndex()
{	
	//1.POS
	m_TextureIndex[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_TextureIndex[1] = D3DXVECTOR2(1.0f / 7.0f, 0.0f);
	m_TextureIndex[2] = D3DXVECTOR2(2.0f / 7.0f, 0.0f);
	m_TextureIndex[3] = D3DXVECTOR2(3.0f / 7.0f, 0.0f);
	m_TextureIndex[4] = D3DXVECTOR2(4.0f / 7.0f, 0.0f);
	m_TextureIndex[5] = D3DXVECTOR2(5.0f / 7.0f, 0.0f);
	m_TextureIndex[6] = D3DXVECTOR2(6.0f / 7.0f, 0.0f);
	m_TextureIndex[7] = D3DXVECTOR2(7.0f / 7.0f, 0.0f);

	//2.POS
	m_TextureIndex[8] = D3DXVECTOR2(0.0f, 1.0f / 4.0f);
	m_TextureIndex[9] = D3DXVECTOR2(1.0f / 7.0f, 1.0f / 4.0f);
	m_TextureIndex[10] = D3DXVECTOR2(2.0f / 7.0f, 1.0f / 4.0f);
	m_TextureIndex[11] = D3DXVECTOR2(3.0f / 7.0f, 1.0f / 4.0f);
	m_TextureIndex[12] = D3DXVECTOR2(4.0f / 7.0f, 1.0f / 4.0f);
	m_TextureIndex[13] = D3DXVECTOR2(5.0f / 7.0f, 1.0f / 4.0f);
	m_TextureIndex[14] = D3DXVECTOR2(6.0f / 7.0f, 1.0f / 4.0f);
	m_TextureIndex[15] = D3DXVECTOR2(7.0f / 7.0f, 1.0f / 4.0f);

	//3.POS
	m_TextureIndex[16] = D3DXVECTOR2(0.0f, 2.0f / 4.0f);
	m_TextureIndex[17] = D3DXVECTOR2(1.0f / 7.0f, 2.0f / 4.0f);
	m_TextureIndex[18] = D3DXVECTOR2(2.0f / 7.0f, 2.0f / 4.0f);
	m_TextureIndex[19] = D3DXVECTOR2(3.0f / 7.0f, 2.0f / 4.0f);
	m_TextureIndex[20] = D3DXVECTOR2(4.0f / 7.0f, 2.0f / 4.0f);
	m_TextureIndex[21] = D3DXVECTOR2(5.0f / 7.0f, 2.0f / 4.0f);
	m_TextureIndex[22] = D3DXVECTOR2(6.0f / 7.0f, 2.0f / 4.0f);
	m_TextureIndex[23] = D3DXVECTOR2(7.0f / 7.0f, 2.0f / 4.0f);

	//5.POS
	m_TextureIndex[24] = D3DXVECTOR2(0.0f, 3.0f / 4.0f);
	m_TextureIndex[25] = D3DXVECTOR2(1.0f / 7.0f, 3.0f / 4.0f);
	m_TextureIndex[26] = D3DXVECTOR2(2.0f / 7.0f, 3.0f / 4.0f);
	m_TextureIndex[27] = D3DXVECTOR2(3.0f / 7.0f, 3.0f / 4.0f);
	m_TextureIndex[28] = D3DXVECTOR2(4.0f / 7.0f, 3.0f / 4.0f);
	m_TextureIndex[29] = D3DXVECTOR2(5.0f / 7.0f, 3.0f / 4.0f);
	m_TextureIndex[30] = D3DXVECTOR2(6.0f / 7.0f, 3.0f / 4.0f);
	m_TextureIndex[31] = D3DXVECTOR2(7.0f / 7.0f, 3.0f / 4.0f);

	//6.POS
	m_TextureIndex[32] = D3DXVECTOR2(0.0f, 1.0f);
	m_TextureIndex[33] = D3DXVECTOR2(1.0f / 7.0f, 1.0f);
	m_TextureIndex[34] = D3DXVECTOR2(2.0f / 7.0f, 1.0f);
	m_TextureIndex[35] = D3DXVECTOR2(3.0f / 7.0f, 1.0f);
	m_TextureIndex[36] = D3DXVECTOR2(4.0f / 7.0f, 1.0f);
	m_TextureIndex[37] = D3DXVECTOR2(5.0f / 7.0f, 1.0f);
	m_TextureIndex[38] = D3DXVECTOR2(6.0f / 7.0f, 1.0f);
	m_TextureIndex[39] = D3DXVECTOR2(7.0f / 7.0f, 1.0f);
}

void SetSide(vector<ST_PNT_VERTEX>& vecVertex, D3DXVECTOR2 one, D3DXVECTOR2 two, D3DXVECTOR2 three, D3DXVECTOR2 four)
{
	vecVertex[0].t = three;
	vecVertex[1].t = one;
	vecVertex[2].t = two;
	vecVertex[3].t = three;
	vecVertex[4].t = two;
	vecVertex[5].t = four;

	vecVertex[6].t = three;
	vecVertex[7].t = two;
	vecVertex[8].t = one;
	vecVertex[9].t = three;
	vecVertex[10].t = four;
	vecVertex[11].t = two;

	vecVertex[12].t = four;
	vecVertex[13].t = two;
	vecVertex[14].t = one;
	vecVertex[15].t = four;
	vecVertex[16].t = one;
	vecVertex[17].t = three;

	vecVertex[18].t = three;
	vecVertex[19].t = one;
	vecVertex[20].t = two;
	vecVertex[21].t = three;
	vecVertex[22].t = two;
	vecVertex[23].t = four;
}

void SetTop(vector<ST_PNT_VERTEX>& vecVertex, D3DXVECTOR2 one, D3DXVECTOR2 two, D3DXVECTOR2 three, D3DXVECTOR2 four)
{
	vecVertex[24].t = two;
	vecVertex[25].t = one;
	vecVertex[26].t = three;
	vecVertex[27].t = two;
	vecVertex[28].t = three;
	vecVertex[29].t = four;
}

void SetBottom(vector<ST_PNT_VERTEX>& vecVertex, D3DXVECTOR2 one, D3DXVECTOR2 two, D3DXVECTOR2 three, D3DXVECTOR2 four)
{
	vecVertex[30].t = one;
	vecVertex[31].t = three;
	vecVertex[32].t = four;
	vecVertex[33].t = one;
	vecVertex[34].t = four;
	vecVertex[35].t = two;
}


void cTextureManager::SetNormal(OBJECT_NAME name, vector<ST_PNT_VERTEX>& vecVertex)
{
	switch (name)
	{
	case OBJECT_DIRT:
	{
		SetSide(vecVertex, m_TextureIndex[3], m_TextureIndex[4], m_TextureIndex[11], m_TextureIndex[12]);
		SetTop(vecVertex, m_TextureIndex[0], m_TextureIndex[1], m_TextureIndex[8], m_TextureIndex[9]);
		SetBottom(vecVertex, m_TextureIndex[2], m_TextureIndex[3], m_TextureIndex[10], m_TextureIndex[11]);
	}break;
	case OBJECT_WOOD:
	{
		SetSide(vecVertex, m_TextureIndex[12], m_TextureIndex[13], m_TextureIndex[20], m_TextureIndex[21]);
		SetTop(vecVertex, m_TextureIndex[13], m_TextureIndex[14], m_TextureIndex[21], m_TextureIndex[22]);
		SetBottom(vecVertex, m_TextureIndex[13], m_TextureIndex[14], m_TextureIndex[21], m_TextureIndex[22]);
	}break;
	case OBJECT_LEAF:
	{
		SetSide(vecVertex, m_TextureIndex[28], m_TextureIndex[29], m_TextureIndex[36], m_TextureIndex[37]);
		SetTop(vecVertex, m_TextureIndex[28], m_TextureIndex[29], m_TextureIndex[36], m_TextureIndex[37]);
		SetBottom(vecVertex, m_TextureIndex[28], m_TextureIndex[29], m_TextureIndex[36], m_TextureIndex[37]);
	}break;
	case OBJECT_STONE:
	{
		SetSide(vecVertex, m_TextureIndex[1], m_TextureIndex[2], m_TextureIndex[9], m_TextureIndex[10]);
		SetTop(vecVertex, m_TextureIndex[1], m_TextureIndex[2], m_TextureIndex[9], m_TextureIndex[10]);
		SetBottom(vecVertex, m_TextureIndex[1], m_TextureIndex[2], m_TextureIndex[9], m_TextureIndex[10]);
	}break;
	case OBJECT_BOARD:
	{
		SetSide(vecVertex, m_TextureIndex[4], m_TextureIndex[5], m_TextureIndex[12], m_TextureIndex[13]);
		SetTop(vecVertex, m_TextureIndex[4], m_TextureIndex[5], m_TextureIndex[12], m_TextureIndex[13]);
		SetBottom(vecVertex, m_TextureIndex[4], m_TextureIndex[5], m_TextureIndex[12], m_TextureIndex[13]);
	}break;
	case OBJECT_STONEBRICK:
	{
		SetSide(vecVertex, m_TextureIndex[5], m_TextureIndex[6], m_TextureIndex[13], m_TextureIndex[14]);
		SetTop(vecVertex, m_TextureIndex[5], m_TextureIndex[6], m_TextureIndex[13], m_TextureIndex[14]);
		SetBottom(vecVertex, m_TextureIndex[5], m_TextureIndex[6], m_TextureIndex[13], m_TextureIndex[14]);
	}break;
	}
}

