#include "stdafx.h"
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

	m_vecVertex[0].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[1].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex[2].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex[3].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[4].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex[5].t = D3DXVECTOR2(0.25, 0.5);

	m_vecVertex[6].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[7].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex[8].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex[9].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[10].t = D3DXVECTOR2(0.25, 0.5);
	m_vecVertex[11].t = D3DXVECTOR2(0.25, 0.25);

	m_vecVertex[12].t = D3DXVECTOR2(0.25, 0.5);
	m_vecVertex[13].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex[14].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex[15].t = D3DXVECTOR2(0.25, 0.5);
	m_vecVertex[16].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex[17].t = D3DXVECTOR2(0, 0.5);

	m_vecVertex[18].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[19].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex[20].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex[21].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[22].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex[23].t = D3DXVECTOR2(0.25, 0.5);

	m_vecVertex[24].t = D3DXVECTOR2(0.75, 0.5);
	m_vecVertex[25].t = D3DXVECTOR2(0.5, 0.5);
	m_vecVertex[26].t = D3DXVECTOR2(0.5, 0.75);
	m_vecVertex[27].t = D3DXVECTOR2(0.75, 0.5);
	m_vecVertex[28].t = D3DXVECTOR2(0.5, 0.75);
	m_vecVertex[29].t = D3DXVECTOR2(0.75, 0.75);

	m_vecVertex[30].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[31].t = D3DXVECTOR2(0, 0.75);
	m_vecVertex[32].t = D3DXVECTOR2(0.25, 0.75);
	m_vecVertex[33].t = D3DXVECTOR2(0, 0.5);
	m_vecVertex[34].t = D3DXVECTOR2(0.25, 0.75);
	m_vecVertex[35].t = D3DXVECTOR2(0.25, 0.5);
}


cTree::~cTree()
{
}

void cTree::Setup()
{

	for (int i = 1; i < 4; i++)
	{
		D3DXVECTOR3 tempPos = m_vLocalPos;
		tempPos.y += i;
		cTree* pTree = new cTree(tempPos);
		
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

	for (int i = 0; i < m_vecTree.size(); i++)
	{
		m_vecTree[i]->SetName("Dirt");
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
