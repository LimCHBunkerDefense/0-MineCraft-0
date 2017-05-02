#include "stdafx.h"
#include "cSun.h"


cSun::cSun()
	: m_pSun(NULL)
	, m_vPosition(0, 0, 0)
	, m_pTexture(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cSun::~cSun()
{
	SAFE_DELETE(m_pSun);
	SAFE_RELEASE(m_pTexture);
}


void cSun::Setup()
{
	cCubePNT::Setup();

	D3DXCreateTextureFromFile(g_pD3DDevice, TEXT("Image/Environment/Sun.png"), &m_pTexture);

	Set_Material();
	Set_Texture();

	float x = -300;
	float y = pow(x, 2) * -(1.0f / 300.0f) + 300;

	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = 300.0f;
}

void cSun::Update()
{
	cCubePNT::Update();

	m_vPosition.x += 0.05f;
	m_vPosition.y = pow(m_vPosition.x, 2) * -(1.0f / 300.0f) + 300;
	
	D3DXMATRIXA16 matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	
	D3DXMatrixScaling(&matS, 80.0f, 80.0f, 80.0f);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matT;

	Set_Light();
}

void cSun::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	cCubePNT::Render();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);
}

D3DXVECTOR3& cSun::GetPosition()
{
	return m_vPosition;
}

void cSun::Set_Light()
{
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
}

void cSun::Set_Material()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);		// 주변광 : 일정한 방향을 가지지 않고 비춤
	m_stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);		// 난반사광 : 특정 방향으로 비춰지지만, 고르게 반사됨
	m_stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);		// 전반사광 : 방향성을 가지며, 특정 방향으로 정확히 반사됨
	m_stMtl.Emissive = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);		// 자체 발광
	 m_stMtl.Power = 5.0f;
}

void cSun::Set_Texture()
{
	// 뒷면
	m_vecVertex[0].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[1].t = D3DXVECTOR2(0.4f, 0.4f);
	m_vecVertex[2].t = D3DXVECTOR2(0.6f, 0.4f);

	m_vecVertex[3].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[4].t = D3DXVECTOR2(0.6f, 0.4f);
	m_vecVertex[5].t = D3DXVECTOR2(0.6f, 0.6f);

	// 앞면
	m_vecVertex[6].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[7].t = D3DXVECTOR2(0.6f, 0.4f);
	m_vecVertex[8].t = D3DXVECTOR2(0.4f, 0.4f);

	m_vecVertex[9].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[10].t = D3DXVECTOR2(0.6f, 0.6f);
	m_vecVertex[11].t = D3DXVECTOR2(0.6f, 0.4f);

	// 왼쪽
	m_vecVertex[12].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[13].t = D3DXVECTOR2(0.4f, 0.4f);
	m_vecVertex[14].t = D3DXVECTOR2(0.6f, 0.4f);

	m_vecVertex[15].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[16].t = D3DXVECTOR2(0.6f, 0.4f);
	m_vecVertex[17].t = D3DXVECTOR2(0.6f, 0.6f);

	// 오른쪽
	m_vecVertex[18].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[19].t = D3DXVECTOR2(0.4f, 0.4f);
	m_vecVertex[20].t = D3DXVECTOR2(0.6f, 0.4f);

	m_vecVertex[21].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[22].t = D3DXVECTOR2(0.6f, 0.4f);
	m_vecVertex[23].t = D3DXVECTOR2(0.6f, 0.6f);

	// 윗면
	m_vecVertex[24].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[25].t = D3DXVECTOR2(0.4f, 0.4f);
	m_vecVertex[26].t = D3DXVECTOR2(0.6f, 0.4f);

	m_vecVertex[27].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[28].t = D3DXVECTOR2(0.6f, 0.4f);
	m_vecVertex[29].t = D3DXVECTOR2(0.6f, 0.6f);

	// 아랫면
	m_vecVertex[30].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[31].t = D3DXVECTOR2(0.4f, 0.4f);
	m_vecVertex[32].t = D3DXVECTOR2(0.6f, 0.4f);

	m_vecVertex[33].t = D3DXVECTOR2(0.4f, 0.6f);
	m_vecVertex[34].t = D3DXVECTOR2(0.6f, 0.4f);
	m_vecVertex[35].t = D3DXVECTOR2(0.6f, 0.6f);
	
}