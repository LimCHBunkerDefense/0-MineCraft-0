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
		string szFilePath ="image/"+ (string)keyName + ".png";
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
