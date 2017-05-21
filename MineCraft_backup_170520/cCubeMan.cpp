#include "stdafx.h"
#include "cCubeMan.h"
#include "cObjectManager.h"
#include "cInputManager.h"
#include "cObject.h"
#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL)
{
	m_currentState = IDLE_STATE;
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
	if (m_tag == CHARACTER_PLAYER)
	{
		GravityUpdate();


		switch (m_currentState)
		{
		case IDLE_STATE: IdleState(); break;
		case MOVE_STATE: MoveState(); break;
		case JUMP_STATE: JumpState(); break;
		}		
	}
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

void cCubeMan::IdleState()
{
	m_isMoving = false;


	if (INPUT->IsKeyPress(VK_A) || INPUT->IsKeyPress(VK_D) || INPUT->IsKeyPress(VK_W) || INPUT->IsKeyPress(VK_S))
	{
		m_currentState = MOVE_STATE;
	}
	if (INPUT->IsKeyPress(VK_SPACE) && m_isFall == false)
	{
		m_currentState = JUMP_STATE;
	}

}

void cCubeMan::MoveState()
{
	m_isMoving = false;

	MovePosition();

	if (INPUT->IsKeyPress(VK_SPACE) && m_isFall == false)
	{
		m_isMoving = true;
		m_currentState = JUMP_STATE;
	}

	if (m_isMoving == false)m_currentState = IDLE_STATE;
}

void cCubeMan::JumpState()
{
	m_isMoving = false;
	m_isJumping = true;
	MovePosition();

	bool isUpCollid = false;

	//하늘방향 충돌체크
	{


		D3DXVECTOR3	intersectDir = D3DXVECTOR3(0, 1, 0);

		vector<cObject*> vecObject = g_ObjectManager->GetNearPlayerVecObject();


		float u, v;
		float dist;


		for (vector<cObject*>::iterator it = vecObject.begin(); it != vecObject.end(); it++)
		{
			D3DXVECTOR3 rayPos = m_vPosition;
			if ((*it)->GetPosition().y >= (this->GetPosition().y + 1.0f))
			{
				vector<ST_PNT_VERTEX> pPNT = (*it)->GetVectex();
				for (int k = 0; k < 2; k++)
				{
					if (D3DXIntersectTri(&pPNT[30 + (k * 3)].p, &pPNT[31 + (k * 3)].p, &pPNT[32 + (k * 3)].p, &rayPos, &intersectDir, &u, &v, &dist))
					{
						if (dist <= 1.4f)isUpCollid = true;
					}
				}
			}
		}
	}



	if (m_jumpingHeight >= m_currentHeight&&isUpCollid == false)
	{
		m_vPosition.y += 0.1f;
		m_currentHeight += 0.1;
	}
	else
	{
		m_currentHeight = 0.0f;
		m_currentState = IDLE_STATE;
		m_isJumping = false;
	}
}

void cCubeMan::GravityUpdate()
{
	D3DXVECTOR3	intersectDir = D3DXVECTOR3(0, -1, 0);

	vector<cObject*> vecObject = g_ObjectManager->GetNearPlayerVecObject();

	D3DXVECTOR3 rayPos = m_vPosition;
	float u, v;
	float dist;
	float tempDist = 0.0f;
	m_isFall = false;
	rayPos.y += 2.0f;

	for (vector<cObject*>::iterator it = vecObject.begin(); it != vecObject.end(); it++)
	{
		vector<ST_PNT_VERTEX> pPNT = (*it)->GetVectex();
		for (int k = 0; k < 2; k++)
		{
			if (D3DXIntersectTri(&pPNT[24 + (k * 3)].p, &pPNT[25 + (k * 3)].p, &pPNT[26 + (k * 3)].p, &rayPos, &intersectDir, &u, &v, &dist))
			{
				tempDist = rayPos.y - dist;
				//isFall = true;
			}
		}

	}

	if (m_vPosition.y > tempDist&&m_isJumping == false)
	{
		m_vPosition.y -= 0.1f;
		m_isFall = true;
	}
	/*if (m_isFall == false)
	{
	m_vPosition.y = tempDist;
	}*/

}

void cCubeMan::MovePosition()
{
	if (!m_isMouseOn)
	{
		if (INPUT->IsKeyPress(VK_A))
		{
			m_isMoving = true;
			m_fRotY -= 0.1f;
		}
		if (INPUT->IsKeyPress(VK_D))
		{
			m_isMoving = true;
			m_fRotY += 0.1f;
		}
	}
	else if (m_isMouseOn)
	{
		POINT deltaPos = INPUT->GetMouseDelta();
		m_fRotY += deltaPos.x * 0.01f;
	}

	if (INPUT->IsKeyPress(VK_W))
	{
		m_isMoving = true;
		CollidChecker(1);
		//m_vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	if (INPUT->IsKeyPress(VK_S))
	{
		m_isMoving = true;
		CollidChecker(-1);
		//m_vPosition = m_vPosition - (m_vDirection * 0.1f);
	}
}
