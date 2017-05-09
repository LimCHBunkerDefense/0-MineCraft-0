#include "stdafx.h"
#include "cAnimal.h"
#include <ctime>
#include <stdio.h>
#include <cmath>

cAnimal::cAnimal()
	:m_fRotY(D3DX_PI),
	m_vDirection(0, 0, -1),
	m_vPosition(0, 0, 0),
	m_prevPosition(0,0,0),
	m_vTargetPos(0,0,0),
	IsRotation(false),
	IsMove(true),
	nMoveCount(0),
	nRotationCount(0),
	nRandCount(0),
	nRandRotation(0)
{
	D3DXMatrixIdentity(&m_matWorld);
	srand((unsigned)time(NULL));
}

cAnimal::~cAnimal()
{
}

void cAnimal::Setup()
{
	int x = rand() % 200 - 100;
	int z = rand() % 200 - 100;
	m_vPosition = D3DXVECTOR3(x, 0, z);
	
	nRandCount = rand() % 230 + 300;
}

void cAnimal::Update()
{	
	//1초당 약 33번 돈다
	
	if (IsMove)
	{
		m_vPosition = m_vPosition - m_vDirection * 0.05f;
		nMoveCount++;
		if (nMoveCount - nRandCount == 0)
		{
			IsMove = false;
			IsRotation = true;
			//2초에서 4초사이가 적당
			nRandCount = rand() % 60 + 70;
			nMoveCount = 0;
		}
	}

	if (IsRotation)
	{
		if (nRandCount % 2 == 0)
		{
			m_fRotY = m_fRotY + 0.008f;
		}
		else
		{
			m_fRotY = m_fRotY - 0.008f;
		}

		nRotationCount++;
		if (nRotationCount - nRandCount == 0)
		{
			IsMove = true;
			IsRotation = false;
			nRandCount = rand() % 230 + 300;
			nRotationCount = 0;
		}
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

void cAnimal::Render()
{

}

D3DXVECTOR3 & cAnimal::GetPosition()
{
	return m_vPosition;
}

D3DXVECTOR3 cAnimal::SetTargetPos()
{
	int x, z;
	x = rand() % 100;
	z = rand() % 100;

	return D3DXVECTOR3(x, 0, z);
}

