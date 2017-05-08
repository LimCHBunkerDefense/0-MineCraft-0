#include "stdafx.h"
#include "cAnimalMan.h"
#include "cAnimalHead.h"
#include "cAnimalBody.h"
#include "cAnimalLeftArm.h"
#include "cAnimalLeftLeg.h"
#include "cAnimalRightArm.h"
#include "cAnimalRightLeg.h"
#include "cAnimalNose.h"

cAnimalMan::cAnimalMan()
	:m_pRoot(NULL)
{
}


cAnimalMan::~cAnimalMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cAnimalMan::Setup()
{
	cAnimal::Setup();
	Set_Material();
	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("Image/Skin/MineCraft_Pig.png"),
		&m_pTexture);

	cAnimalBody * pBody = new cAnimalBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;

	cAnimalHead * pHead = new cAnimalHead;
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	cAnimalLeftArm * pLeftArm = new cAnimalLeftArm;
	pLeftArm->Setup();
	pLeftArm->SetRotDeltaX(0.05f);
	m_pRoot->AddChild(pLeftArm);

	cAnimalRightArm * pRightArm = new cAnimalRightArm;
	pRightArm->Setup();
	pRightArm->SetRotDeltaX(-0.05f);
	m_pRoot->AddChild(pRightArm);

	cAnimalLeftLeg * pLeftLeg = new cAnimalLeftLeg;
	pLeftLeg->Setup();
	pLeftLeg->SetRotDeltaX(-0.05f);
	m_pRoot->AddChild(pLeftLeg);

	cAnimalRightLeg * pRightLeg = new cAnimalRightLeg;
	pRightLeg->Setup();
	pRightLeg->SetRotDeltaX(0.05f);
	m_pRoot->AddChild(pRightLeg);

	cAnimalNose * pNose = new cAnimalNose;
	pNose->Setup();
	m_pRoot->AddChild(pNose);
}

void cAnimalMan::Update()
{
	cAnimal::Update();
	if (m_pRoot)
		m_pRoot->Update();
}

void cAnimalMan::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetMaterial(&m_stMtl);

	cAnimal::Render();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	if (m_pRoot)
		m_pRoot->Render();
}

void cAnimalMan::Set_Material()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}
