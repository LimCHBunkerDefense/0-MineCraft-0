#include "stdafx.h"
#include "cCubeMan.h"

#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL)
{
}


cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();

	SAFE_RELEASE(m_pTexture); 

}

void cCubeMan::Setup()
{
	cCharacter::Setup(); 

	Set_Material(); 

	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("Image/Skin/batman.png"), &m_pTexture); 


	cBody * pBody = new cBody; 
	pBody->SetScale(m_fScale);
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld); 
	m_pRoot = pBody; 

	cHead * pHead = new cHead;
	pHead->SetScale(m_fScale);
	pHead->Setup();
	m_pRoot->AddChild(pHead); 

	cLeftArm * pLeftArm = new cLeftArm;
	pLeftArm->SetScale(m_fScale);
	pLeftArm->Setup();
	pLeftArm->SetRotDeltaX(0.1f); 
	m_pRoot->AddChild(pLeftArm);

	cRightArm * pRightArm = new cRightArm;
	pRightArm->SetScale(m_fScale);
	pRightArm->Setup();
	pRightArm->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pRightArm);

	cLeftLeg * pLeftLeg = new cLeftLeg;
	pLeftLeg->SetScale(m_fScale);
	pLeftLeg->Setup();
	pLeftLeg->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pLeftLeg);

	cRightLeg * pRightLeg = new cRightLeg;
	pRightLeg->SetScale(m_fScale);
	pRightLeg->Setup();
	pRightLeg->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pRightLeg);
}

void cCubeMan::Update()
{
	cCharacter::Update(); 

	if (m_pRoot)
	{
		if (m_isMoving) m_pRoot->RotateRotX();
		if (!m_isMoving)m_pRoot->SetDefaultRotX();
		if (m_isAttack) m_pRoot->AttackMotion();
		if (!m_isAttack) m_pRoot->EndAttack();
		m_pRoot->Update();
	}
	
}

void cCubeMan::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true); 
	g_pD3DDevice->SetMaterial(&m_stMtl); 

	cCharacter::Render();

	D3DXMATRIXA16 matWorld; 
	D3DXMatrixIdentity(&matWorld); 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetTexture(0, m_pTexture); 

	if (m_pRoot)
		m_pRoot->Render(); 

	g_pD3DDevice->SetTexture(0, NULL);
}

void cCubeMan::Set_Material()
{   
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	m_stMtl.Emissive = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void cCubeMan::SetScale(float scale)
{
	m_fScale = scale;
}

void cCubeMan::LookAt(D3DXVECTOR2 lookAt)
{
	D3DXVECTOR2 headPos = D3DXVECTOR2(m_vPosition.x + VIEW_WIDTH * 0.5f, m_vPosition.y);
	
	float deltaX = (lookAt.x - headPos.x) * -1;
	float deltaY = (lookAt.y - headPos.y);

	float angleX = deltaY * 0.005;
	if (angleX > D3DX_PI * 0.15) angleX = D3DX_PI * 0.15;
	else if (angleX < -D3DX_PI * 0.15) angleX = -D3DX_PI * 0.15;
	float angleY = deltaX * 0.005;
	if (angleY > D3DX_PI * 0.2) angleY = D3DX_PI * 0.2;
	else if (angleY < -D3DX_PI * 0.2) angleY = -D3DX_PI * 0.2;

	m_pRoot->RotateHead(angleX, angleY);
}