#include "stdafx.h"
#include "cTextureManager.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cTree.h"



cTree::cTree()
{
}

cTree::cTree(D3DXVECTOR3 pos)
{
	cCubePNT::Setup();

	m_vLocalPos = pos;
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y + 0.5f, m_vLocalPos.z);
	for (int i = 0; i < m_vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matT);
}


cTree::~cTree()
{
}

void cTree::Setup()
{
	vector<cObject*>& pObject = g_ObjectManager->GetVecObject();
	for (int i = 1; i < 4; i++)
	{
		D3DXVECTOR3 tempPos = m_vLocalPos;
		tempPos.y += i;
		cTree* pTree = new cTree(tempPos);
		pTree->SetName(OBJECT_WOOD);
		g_pTextureManager->SetNormal(OBJECT_WOOD, pTree->GetVectex());
		
		m_vecTree.push_back(pTree);
	}
	D3DXVECTOR3 tempPos = m_vecTree[0]->GetPosition();

	for (int i = 0; i < 3; i++)
	{
		tempPos.y += 1;
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x - 1, tempPos.y, tempPos.z - 1)));
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x - 1, tempPos.y, tempPos.z)));
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x - 1, tempPos.y, tempPos.z + 1)));
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x , tempPos.y, tempPos.z-1)));
		if(i==2)m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x , tempPos.y, tempPos.z )));
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x , tempPos.y, tempPos.z + 1)));
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x + 1, tempPos.y, tempPos.z - 1)));
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x + 1, tempPos.y, tempPos.z)));
		m_vecTree.push_back(new cTree(D3DXVECTOR3(tempPos.x + 1, tempPos.y, tempPos.z + 1)));
	}

	for (int i = 3; i < m_vecTree.size(); i++)
	{
		m_vecTree[i]->SetName(OBJECT_LEAF);
		g_pTextureManager->SetNormal(OBJECT_LEAF, m_vecTree[i]->GetVectex());
	}

	for (int i = 0; i < m_vecTree.size(); i++)
	{
		pObject.push_back(m_vecTree[i]);
	}
}

void cTree::Render()
{
	cCubePNT::Render();
	for (int i = 0; i < m_vecTree.size(); i++)
	{
		m_vecTree[i]->Render();
	}
}

void cTree::SetWood()
{
}

void cTree::SetLeaf()
{
}
