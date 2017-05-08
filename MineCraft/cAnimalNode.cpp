#include "stdafx.h"
#include "cAnimalNode.h"


cAnimalNode::cAnimalNode()
	:m_fRotDeltaX(0.0f), m_pParentWorldTM(NULL), m_vLocalPos(0, 0, 0), m_fRotX(0.0f)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cAnimalNode::~cAnimalNode()
{
}

void cAnimalNode::AddChild(cAnimalNode* pChild)
{
	pChild->m_pParentWorldTM = &m_matWorldTM;
	m_vecChild.push_back(pChild);
}

void cAnimalNode::Destroy()
{
	for each(auto p in m_vecChild)
	{
		p->Destroy();
	}
	delete this;
}

void cAnimalNode::Setup()
{
	cAnimalPNT::Setup();
}

void cAnimalNode::Update()
{
	cAnimalPNT::Update();

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
	}

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

void cAnimalNode::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);

	cAnimalPNT::Render();
	for each(auto p in m_vecChild)
		p->Render();
}