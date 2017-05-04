#include "stdafx.h"
#include "cObjectManager.h"
#include "cTextureManager.h"
#include "cObject.h"
#include "cTree.h"


cObjectManager::cObjectManager()
{
	//m_vecObject.reserve(10000);
}


cObjectManager::~cObjectManager()
{
	for (vector<cObject*>::iterator it = m_vecObject.begin(); it != m_vecObject.end(); it++)
	{
		delete (*it);
	}
	m_vecObject.clear();
}

void cObjectManager::Render(D3DXVECTOR3 pos)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	
	for (vector<cObject*>::iterator it = m_vecObject.begin(); it != m_vecObject.end(); it++)
	{		
	/*for(int i=0;i<1000000;i++)
	{*/
		/*if ((*it)->GetName() == OBJECT_WOOD)
		{
			g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		}*/
		if((pos.x-100 <= (*it)->GetPosition().x&&(*it)->GetPosition().x<=pos.x+100)&& (pos.z - 100 <= (*it)->GetPosition().z && (*it)->GetPosition().z <= pos.z + 100))
		(*it)->Render();
	}
}

void cObjectManager::CreateObject(D3DXVECTOR3 targetPos, OBJECT_NAME name)
{
		cObject* pObject = NULL;
		switch (name)
		{
		//case OBJECT_DIRT: pObject = new cObject(targetPos); break;
		case OBJECT_WOOD:  pObject = new cTree(targetPos);  break;
		default :pObject = new cObject(targetPos); break;
		}
		if (pObject != NULL) 
		{
			//m_vecObject.resize(m_vecObject.size() + 1);
			pObject->SetName(name);
			g_pTextureManager->SetNormal(pObject->GetName(), pObject->GetVectex());
			pObject->Setup();
			m_vecObject.push_back(pObject);
		}
}

bool cObjectManager::IsObjectHere(D3DXVECTOR3 targetPos)
{
	for (vector<cObject*>::iterator it = m_vecObject.begin(); it != m_vecObject.end(); it++)
	{
	if ((*it)->GetPosition() == targetPos)return false;
	}
	return true;
}
