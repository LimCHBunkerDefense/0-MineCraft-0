#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	: m_fRotDeltaX(0.0f),
	m_pParentWorldTM(NULL),
	m_vLocalPos(0, 0, 0)
	, m_fRotX(0.0f)
	, m_fScale(1.0f),
	m_fAttackRotX(0),
	m_fAttackDir(0.5f)

	// << : 
{
	D3DXMatrixIdentity(&m_matLocalTM); 
	D3DXMatrixIdentity(&m_matWorldTM);
}


cCubeNode::~cCubeNode()
{
}

void cCubeNode::Setup()
{
	// : to do someting 
	cCubePNT::Setup(); 
}
void cCubeNode::Update()
{
	// : to do someting
	cCubePNT::Update();

	D3DXMATRIXA16 matR, matT; 
	D3DXMatrixIdentity(&matR); 
	D3DXMatrixIdentity(&matT);

	D3DXMatrixRotationX(&matR, m_fRotX); // : 
	D3DXMatrixTranslation(&matT, m_vLocalPos.x,
		m_vLocalPos.y,
		m_vLocalPos.z);

	m_matLocalTM = matR * matT; 

	m_matWorldTM = m_matLocalTM; 

	if (m_pParentWorldTM)
		m_matWorldTM *= *m_pParentWorldTM; 


	for each (auto p in m_vecChild)
	{
		p->Update();
	}
}

void cCubeNode::Render()
{
	// : to do someting 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM); 

	cCubePNT::Render(); 
	for each(auto p in m_vecChild)
		p->Render(); 
}


void cCubeNode::AddChild(cCubeNode* pChild)
{
	// : to do someting 
	pChild->m_pParentWorldTM = &m_matWorldTM; 
	m_vecChild.push_back(pChild); 
}

void cCubeNode::RotateRotX()
{
	m_fRotX += m_fRotDeltaX;
	if (m_fRotX > D3DX_PI / 6.0f)
	{
		m_fRotX = D3DX_PI / 6.0f;
		m_fRotDeltaX *= -1;
	}

	if (m_fRotX < -D3DX_PI / 6.0f)
	{
		m_fRotX = -D3DX_PI / 6.0f;
		m_fRotDeltaX *= -1;
	}

	for each(auto p in m_vecChild)
	{
		p->RotateRotX();
	}
}

void cCubeNode::SetDefaultRotX()
{
	SetRotX(0.0f);
	
	for (int i = 0; i < m_vecChild.size(); i++)
	{
		if (i == 0) continue;					// 해당 cpp에서 RotateHead함수를 위해 0번을 빼놓도록 함(0번은 머리)
		m_vecChild[i]->SetDefaultRotX();
	}
}

void cCubeNode::Destroy()
{
	// : to do someting 
	for each(auto p in m_vecChild)
	{
		p->Destroy(); 
	}
	delete this; 
}

void cCubeNode::AttackMotion()
{
	if (m_fAttackRotX < -3)m_fAttackDir = -m_fAttackDir;
	if (m_fAttackRotX > 0)m_fAttackDir = -m_fAttackDir;
	m_fAttackRotX += m_fAttackDir;


	m_vecChild[2]->SetRotX(m_fAttackRotX);
}

void cCubeNode::EndAttack()
{
	m_vecChild[2]->SetRotX(-m_vecChild[1]->GetRotX());
}

void cCubeNode::SetScale(float scale)
{
	m_fScale = scale ;
}

void cCubeNode::RotateHead(float angleX, float angleY)
{
	if (m_vecChild.size() == 0)
	{
		D3DXMATRIXA16 matRX, matRY, matR, mat, matT;
		//D3DXMatrixTranslation(&matT, 0, -1.4, 0);
		//
		//for (size_t i = 0; i < m_vecVertex.size(); i++)
		//{
		//	D3DXVec3TransformCoord(&m_vecVertex[i].p,
		//		&m_vecVertex[i].p,
		//		&matT);
		//}
		//
		//D3DXMatrixIdentity(&matT);
		//D3DXMatrixTranslation(&matT, 0, 1.4, 0);
		D3DXMatrixRotationX(&matRX, angleX - m_fRotX);
		D3DXMatrixRotationY(&matRY, angleY - m_fRotY);
		matR = matRX * matRY;
		mat = matR;//  *matT;

		for (size_t i = 0; i < m_vecVertex.size(); i++)
		{
			D3DXVec3TransformCoord(&m_vecVertex[i].p,
				&m_vecVertex[i].p,
				&mat);
		}
	}
	
	else
	{
		m_vecChild[0]->RotateHead(angleX, angleY);
		m_vecChild[0]->SetRotX(angleX);
		m_vecChild[0]->SetRotY(angleY);
	
	}
	
}