#include "stdafx.h"
#include "cCharacter.h"
#include "cInputManager.h"
#include "cObjectManager.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f) ,
	m_vDirection(0,0,1), 
	m_vPosition(0,0,0),
	m_vFrontPos(0,0,0),
	m_isMoving(false)
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
	m_isMoving = false;

	if (INPUT->IsKeyPress('A'))
	{
		m_isMoving = true;
		m_fRotY -= 0.1f;
	}
	if (INPUT->IsKeyPress('D'))
	{
		m_isMoving = true;
		m_fRotY += 0.1f;
	}

	if (INPUT->IsKeyPress('W'))
	{
		m_isMoving = true;
		m_vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	if (INPUT->IsKeyPress('S'))
	{
		m_isMoving = true;
		m_vPosition = m_vPosition - (m_vDirection * 0.1f);
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;

	// >> : update frontPos
	float angle;
	if(m_vDirection.x <= 0) angle = acosf(D3DXVec3Dot(&D3DXVECTOR3(0.0f, m_vDirection.y, 1.0f), &m_vDirection));
	else if(m_vDirection.x > 0) angle = D3DX_PI * 2 - acosf(D3DXVec3Dot(&D3DXVECTOR3(0.0f, m_vDirection.y, 1.0f), &m_vDirection));

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
	if (INPUT->IsKeyPress('E'))
	{
		g_ObjectManager->CreateObject(m_vFrontPos);
	}
}
void cCharacter::Render()
{

}
D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}

D3DXVECTOR3& cCharacter::GetFrontPos()
{
	return m_vFrontPos;
}

D3DXVECTOR3 & cCharacter::GetDirection()
{
	return m_vDirection;
}
