#include "stdafx.h"
#include "cCharacter.h"
#include "cInputManager.h"
#include "cObjectManager.h"
#include "cObject.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f),
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0, 0),
	m_vFrontPos(0, 0, 0),
	m_isMoving(false),
	m_isJumping(false),
	m_isFall(false),
	m_fPrevY(0),
	m_fScale(1.0f),
	m_tag(CHARACTER_PLAYER),
	m_currentObjName(OBJECT_NONE),
	m_jumpingHeight(1.5f),
	m_currentHeight(0.0f),
	m_isMouseOn(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{

}
void cCharacter::Update()
{
	//if (m_tag == CHARACTER_PLAYER)
	//{
	//	m_isMoving = false;

		

	//	if (INPUT->IsKeyPress(VK_W))
	//	{
	//		m_isMoving = true;
	//		CollidChecker(1);
	//		//m_vPosition = m_vPosition + (m_vDirection * 0.1f);
	//	}
	//	if (INPUT->IsKeyPress(VK_S))
	//	{
	//		m_isMoving = true;
	//		CollidChecker(-1);
	//		//m_vPosition = m_vPosition - (m_vDirection * 0.1f);
	//	}
	//}

	if (m_tag == CHARACTER_PLAYER)
	{
		if (INPUT->IsKeyPress(VK_1))m_currentObjName = OBJECT_DIRT;
		if (INPUT->IsKeyPress(VK_2))m_currentObjName = OBJECT_STONE;
		if (INPUT->IsKeyPress(VK_3))m_currentObjName = OBJECT_BOARD;
		if (INPUT->IsKeyPress(VK_4))m_currentObjName = OBJECT_STONEBRICK;
		if (INPUT->IsKeyPress(VK_5))m_currentObjName = OBJECT_WOOD;
		if (INPUT->IsKeyDown(VK_TAB))m_currentObjName = OBJECT_NONE;
	
		if (INPUT->IsKeyPress(VK_E) && m_currentObjName != OBJECT_NONE&&g_ObjectManager->IsObjectHere(m_vFrontPos))
			if (INPUT->IsKeyPress(VK_E))
			{
				m_isAttack = true;
				if (!(m_vPosition.x - 0.7f < m_vFrontPos.x&&m_vFrontPos.x < m_vPosition.x + 0.7f && m_vPosition.z - 0.7f < m_vFrontPos.z&&m_vFrontPos.z < m_vPosition.z + 0.7f)|| !(m_vPosition.y - 0.8f < m_vFrontPos.y&&m_vFrontPos.y < m_vPosition.y + 0.8f))
				{
					g_ObjectManager->CreateObject(m_vFrontPos, m_currentObjName);
				}
			}
		if (INPUT->IsKeyUp(VK_E))
		{
			m_isAttack = false;
		}
		// >> : update frontPos
		float angle;
		if (m_vDirection.x <= 0) angle = acosf(D3DXVec3Dot(&D3DXVECTOR3(0.0f, m_vDirection.y, 1.0f), &m_vDirection));
		else if (m_vDirection.x > 0) angle = D3DX_PI * 2 - acosf(D3DXVec3Dot(&D3DXVECTOR3(0.0f, m_vDirection.y, 1.0f), &m_vDirection));

		D3DXVECTOR3 tempPos;
		if ((angle >= 0.0f && angle < D3DX_PI / 8 * 1) ||
			(angle >= D3DX_PI / 8 * 15 && angle < D3DX_PI / 8 * 16))	tempPos = D3DXVECTOR3(0.0f, 0.01f, 1.0f);			// Á¤¸é
		else if (angle >= D3DX_PI / 8 * 1 && angle < D3DX_PI / 8 * 3)	tempPos = D3DXVECTOR3(-1.0f, 0.01f, 1.0f);			// ÁÂÁ¤¸é
		else if (angle >= D3DX_PI / 8 * 3 && angle < D3DX_PI / 8 * 5)	tempPos = D3DXVECTOR3(-1.0f, 0.01f, 0.0f);			// ÁÂÃø
		else if (angle >= D3DX_PI / 8 * 5 && angle < D3DX_PI / 8 * 7)	tempPos = D3DXVECTOR3(-1.0f, 0.01f, -1.0f);			// ÁÂÈÄ¸é
		else if (angle >= D3DX_PI / 8 * 7 && angle < D3DX_PI / 8 * 9)	tempPos = D3DXVECTOR3(0.0f, 0.01f, -1.0f);			// ÈÄ¸é
		else if (angle >= D3DX_PI / 8 * 9 && angle < D3DX_PI / 8 * 11)	tempPos = D3DXVECTOR3(1.0f, 0.01f, -1.0f);			// ¿ìÈÄ¸é
		else if (angle >= D3DX_PI / 8 * 11 && angle < D3DX_PI / 8 * 13)	tempPos = D3DXVECTOR3(1.0f, 0.01f, 0.0f);			// ¿ìÃø
		else if (angle >= D3DX_PI / 8 * 13 && angle < D3DX_PI / 8 * 15)	tempPos = D3DXVECTOR3(1.0f, 0.01f, 1.0f);			// ¿ìÁ¤¸é
		m_vFrontPos = D3DXVECTOR3((int)m_vPosition.x, (int)m_vPosition.y, (int)m_vPosition.z) + tempPos;
		// << 
	}


	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
	 
	//if (INPUT->IsKeyDown(' ') && !m_isJumping && m_tag == CHARACTER_PLAYER)m_isJumping = true;

	//if (m_isJumping)
	//{
	//	if (m_jumpingHeight >= m_currentHeight)
	//	{
	//		//m_vPosition.y += 0.25f;
	//		m_currentHeight += 0.1;
	//	}
	//}
	//if (m_jumpingHeight <= m_currentHeight)
	//{
	//	m_isJumping = false;
	//}
}
void cCharacter::Render()
{

}
D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}

void cCharacter::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

D3DXVECTOR3& cCharacter::GetFrontPos()
{
	return m_vFrontPos;
}

D3DXVECTOR3 & cCharacter::GetDirection()
{
	return m_vDirection; 
}

void cCharacter::SetScale(float scale)
{

}

void cCharacter::SetRotY(float rotY)
{
	m_fRotY = rotY;
}

void cCharacter::SetTag(CHARACTER_TAG tag)
{
	m_tag = tag;
}

void cCharacter::SetAttackState(bool a)
{
	m_isAttack = a;
}

void cCharacter::SetJumpingState(bool j)
{
	m_isJumping = j;
}

void cCharacter::CollidChecker(int root)
{
	D3DXVECTOR3	intersectDir;
	switch (root)
	{
	case 1:intersectDir = m_vDirection * 1; break;
	case -1:intersectDir = m_vDirection * -1; break;
	}

	vector<cObject*> vecObject = g_ObjectManager->GetNearPlayerVecObject();
	bool isWayBlocked = false;

	for (vector<cObject*>::iterator it = vecObject.begin(); it != vecObject.end(); it++)
	{
		D3DXVECTOR3 rayPos = m_vPosition;
		float u, v;
		float dist;
		if (rayPos.y < rayPos.y + 0.6f)rayPos.y += 0.6f;

		vector<ST_PNT_VERTEX> pPNT = (*it)->GetVectex();
		for (int k = 0; k < 8; k++)
		{
			if (D3DXIntersectTri(&pPNT[0 + (k * 3)].p, &pPNT[1 + (k * 3)].p, &pPNT[2 + (k * 3)].p, &rayPos, &intersectDir, &u, &v, &dist))
			{
				if (dist < 0.6f) { isWayBlocked = true; }
			}

		}
	}
	if (isWayBlocked == false)m_vPosition = m_vPosition + root*(m_vDirection * 0.05f);
}

void cCharacter::FallUpdate()
{
	



}

void cCharacter::SetMouseOn()
{
	m_isMouseOn = !m_isMouseOn;
}
