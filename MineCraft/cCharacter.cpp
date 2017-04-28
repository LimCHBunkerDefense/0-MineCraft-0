#include "stdafx.h"
#include "cCharacter.h"
#include "cInputManager.h"


cCharacter::cCharacter()
	// : to do someting
	: m_fRotY(0.0f) ,
	m_vDirection(0,0,1), 
	m_vPosition(0,0,0)
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
	// : to do someting
	if (INPUT->IsKeyPress('A'))
	{
		m_fRotY -= 0.1f;
	}
	if (INPUT->IsKeyPress('D'))
	{
		m_fRotY += 0.1f;
	}

	if (INPUT->IsKeyPress('W'))
	{
		m_vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	if (INPUT->IsKeyPress('S'))
	{
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

}
void cCharacter::Render()
{

}
D3DXVECTOR3 & cCharacter::GetPosition()
{
	// : to do someting
	return m_vPosition;
}
