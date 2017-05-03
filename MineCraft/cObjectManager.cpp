#include "stdafx.h"
#include "cObjectManager.h"
#include "cTextureManager.h"
#include "cObject.h"
#include "cTree.h"


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
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	for (vector<cObject*>::iterator it = m_vecObject.begin(); it != m_vecObject.end(); it++)
	{
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("Image"));
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
		cObject* pObject = new cTree(tagetPos);
		pObject->SetName(OBJECT_WOOD);
		g_pTextureManager->SetNormal(pObject->GetName(), pObject->GetVectex());
		pObject->Setup();
		m_vecObject.push_back(pObject);
	}

}
