#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("image/Dirt.png"), &m_mapTexture["Dirt"]);
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
		string szFilePath ="image/Texture/"+ (string)keyName + ".png";  // 텍스쳐 이미지 기본경로.
		D3DXCreateTextureFromFile(g_pD3DDevice, (LPCWSTR)((char*)szFilePath.c_str()), &m_mapTexture[keyName]);
	}
	return m_mapTexture[keyName];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(string & keyName)
{
	return GetTexture((char*)keyName.c_str());
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}


void cTextureManager::TextureIdexPos()
{
	map<float, D3DXVECTOR2> m_mapIndex;
	
	//1.POS
	m_mapIndex[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_mapIndex[1] = D3DXVECTOR2(1.0f / 7.0f, 0.0f);
	m_mapIndex[2] = D3DXVECTOR2(2.0f / 7.0f, 0.0f);
	m_mapIndex[3] = D3DXVECTOR2(3.0f / 7.0f, 0.0f);
	m_mapIndex[4] = D3DXVECTOR2(4.0f / 7.0f, 0.0f);
	m_mapIndex[5] = D3DXVECTOR2(5.0f / 7.0f, 0.0f);
	m_mapIndex[6] = D3DXVECTOR2(6.0f / 7.0f, 0.0f);
	m_mapIndex[7] = D3DXVECTOR2(1.0f, 0.0f);

	//2.POS
	m_mapIndex[8] = D3DXVECTOR2(0.0f, 1.0f / 4.0f);
	m_mapIndex[9] = D3DXVECTOR2(1.0f / 7.0f, 1.0f / 4.0f);
	m_mapIndex[10] = D3DXVECTOR2(2.0f / 7.0f, 1.0f / 4.0f);
	m_mapIndex[11] = D3DXVECTOR2(3.0f / 7.0f, 1.0f / 4.0f);
	m_mapIndex[12] = D3DXVECTOR2(4.0f / 7.0f, 1.0f / 4.0f);
	m_mapIndex[13] = D3DXVECTOR2(5.0f / 7.0f, 1.0f / 4.0f);
	m_mapIndex[14] = D3DXVECTOR2(6.0f / 7.0f, 1.0f / 4.0f);
	m_mapIndex[15] = D3DXVECTOR2(1.0f, 1.0f / 4.0f);

	//3.POS
	m_mapIndex[16] = D3DXVECTOR2(0.0f, 2.0f / 4.0f);
	m_mapIndex[17] = D3DXVECTOR2(1.0f / 7.0f, 2.0f / 4.0f);
	m_mapIndex[18] = D3DXVECTOR2(2.0f / 7.0f, 2.0f / 4.0f);
	m_mapIndex[19] = D3DXVECTOR2(3.0f / 7.0f, 2.0f / 4.0f);
	m_mapIndex[20] = D3DXVECTOR2(4.0f / 7.0f, 2.0f / 4.0f);
	m_mapIndex[21] = D3DXVECTOR2(5.0f / 7.0f, 2.0f / 4.0f);
	m_mapIndex[22] = D3DXVECTOR2(6.0f / 7.0f, 2.0f / 4.0f);
	m_mapIndex[23] = D3DXVECTOR2(1.0f, 2.0f / 4.0f);

	//5.POS
	m_mapIndex[24] = D3DXVECTOR2(0.0f, 3.0f / 4.0f);
	m_mapIndex[25] = D3DXVECTOR2(1.0f / 7.0f, 3.0f / 4.0f);
	m_mapIndex[26] = D3DXVECTOR2(2.0f / 7.0f, 3.0f / 4.0f);
	m_mapIndex[27] = D3DXVECTOR2(3.0f / 7.0f, 3.0f / 4.0f);
	m_mapIndex[28] = D3DXVECTOR2(4.0f / 7.0f, 3.0f / 4.0f);
	m_mapIndex[29] = D3DXVECTOR2(5.0f / 7.0f, 3.0f / 4.0f);
	m_mapIndex[30] = D3DXVECTOR2(6.0f / 7.0f, 3.0f / 4.0f);
	m_mapIndex[31] = D3DXVECTOR2(1.0f, 3.0f / 4.0f);

	//6.POS
	m_mapIndex[32] = D3DXVECTOR2(0.0f, 1.0f);
	m_mapIndex[33] = D3DXVECTOR2(1.0f / 7.0f, 1.0f);
	m_mapIndex[34] = D3DXVECTOR2(2.0f / 7.0f, 1.0f);
	m_mapIndex[35] = D3DXVECTOR2(3.0f / 7.0f, 1.0f);
	m_mapIndex[36] = D3DXVECTOR2(4.0f / 7.0f, 1.0f);
	m_mapIndex[37] = D3DXVECTOR2(5.0f / 7.0f, 1.0f);
	m_mapIndex[38] = D3DXVECTOR2(6.0f / 7.0f, 1.0f);
	m_mapIndex[39] = D3DXVECTOR2(1.0f, 1.0f);
}
