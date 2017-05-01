#include "stdafx.h"
#include "cObjectManager.h"
#include "cObject.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
	for (vector<cObject*>::iterator it = m_vecObject.begin(); it != m_vecObject.end(); it++)
	{
		delete (*it);
	}
	m_vecObject.clear();
}

void cObjectManager::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (vector<cObject*>::iterator it = m_vecObject.begin(); it != m_vecObject.end(); it++)
	{
		(*it)->Render();
	}
}

void cObjectManager::CreateObject(D3DXVECTOR3 tagetPos)
{
	bool isTargetEmpty = true;
	for (vector<cObject*>::iterator it = m_vecObject.begin(); it != m_vecObject.end(); it++)
	{
		if ((*it)->GetPosition() == tagetPos)isTargetEmpty = false;
	}
	if (isTargetEmpty == true)
	{
		cObject* pObject = new cObject(tagetPos);
		m_vecObject.push_back(pObject);
	}

}
