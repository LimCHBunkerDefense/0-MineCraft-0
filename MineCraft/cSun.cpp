#include "stdafx.h"
#include "cSun.h"


cSun::cSun()
	: m_pSun(NULL)
	, m_vPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cSun::~cSun()
{
	SAFE_DELETE(m_pSun);
	//SAFE_RELEASE(m_pTexture);
}


void cSun::Setup()
{
	cCubePNT::Setup();

	float x = -300;
	float y = pow(x, 2) * -(1.0f / 300.0f) + 300;

	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = 200.0f;
}

void cSun::Update()
{
	cCubePNT::Update();

	m_vPosition.x += 0.05f;
	m_vPosition.y = pow(m_vPosition.x, 2) * -(1.0f / 300.0f) + 300;

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matT;

	// D3DLIGHT9 stLight_Pnt;
	// ZeroMemory(&stLight_Pnt, sizeof(D3DLIGHT9));
	// 
	// stLight_Pnt.Type = D3DLIGHT_POINT;
	// stLight_Pnt.Ambient = D3DXCOLOR(1.0f, 1.0f, 0.0f, 10.f);
	// stLight_Pnt.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 10.f);
	// stLight_Pnt.Specular = D3DXCOLOR(1.0f, 1.0f, 0.0f, 10.f);
	// stLight_Pnt.Range = 6.5f;
	// stLight_Pnt.Attenuation0 = 0.0f;
	// stLight_Pnt.Attenuation1 = 0.0f;
	// stLight_Pnt.Attenuation2 = 0.0f;
	// stLight_Pnt.Position = D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z);

	D3DLIGHT9	stLight_Dir;
	ZeroMemory(&stLight_Dir, sizeof(D3DLIGHT9));

	stLight_Dir.Type = D3DLIGHT_DIRECTIONAL;
	stLight_Dir.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	stLight_Dir.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight_Dir.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 vDir = -m_vPosition;
	D3DXVec3Normalize(&vDir, &vDir);
	stLight_Dir.Direction = vDir;

	g_pD3DDevice->SetLight(0, &stLight_Dir);
	g_pD3DDevice->LightEnable(0, true);

	g_pD3DDevice->SetTexture(0, NULL);

}

void cSun::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	Set_Material();

	cCubePNT::Render();
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