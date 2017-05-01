#include "stdafx.h"
#include "cSun.h"
#include "cPlanet.h"

cSun::cSun()
	: m_vPosition(0, 0, 0)
{
}


cSun::~cSun()
{
}

void cSun::Setup()
{

}

void cSun::Update()
{

}

void cSun::Render()
{

}

D3DXVECTOR3& cSun::GetPosition()
{
	return m_vPosition;
}

void cSun::Set_Material()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 주변광 : 일정한 방향을 가지지 않고 비춤
	m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 난반사광 : 특정 방향으로 비춰지지만, 고르게 반사됨
	m_stMtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 전반사광 : 방향성을 가지며, 특정 방향으로 정확히 반사됨
	m_stMtl.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 자체 발광
	m_stMtl.Power = 5.0f;
}