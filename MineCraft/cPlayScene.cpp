#include "stdafx.h"
#include "cPlayScene.h"
#include "cObjectManager.h"
#include "cDeviceManager.h"	
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cSurface.h"


cPlayScene::cPlayScene() :
	m_pCubeMan(NULL),
	m_pCamera(NULL),
	m_pTop(NULL),
	m_pBottom(NULL),
	m_pSide1(NULL),
	m_pSide2(NULL),
	m_pSide3(NULL),
	m_pSide4(NULL),
	m_pPosToCreateTile(NULL)
{
}


cPlayScene::~cPlayScene()
{
	SAFE_DELETE(m_pCubeMan);
	SAFE_DELETE(m_pTop);
	SAFE_DELETE(m_pBottom);
	SAFE_DELETE(m_pSide1);
	SAFE_DELETE(m_pSide2);
	SAFE_DELETE(m_pSide3);
	SAFE_DELETE(m_pSide4);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPosToCreateTile);
	g_pDeviceManager->Destroy();
}

void cPlayScene::Setup()
{
	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	m_pPosToCreateTile = new cSurface();
	m_pPosToCreateTile->Setup(D3DXVECTOR3 (-1.0f, 0.0f, -1.0f), D3DXVECTOR3 (-1.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, -1.0f), TEXT("Image/Surface/yellow.png"));

	m_pTop = new cSurface();
	//m_pTop->Setup(-300.0f, 300.0f, 300.0f, -300.0f, 300.0f, -300.0f, 300.0f, 300.0f, -300.0f, 300.0f, 300.0f, 300.0f, TEXT("Image/Surface/?????.png"));	// top이미지 필요
	m_pBottom = new cSurface();
	m_pBottom->Setup(D3DXVECTOR3 (-300.0f, 0.0f, -300.0f), D3DXVECTOR3 (-300.0f, 0.0f, 300.0f), D3DXVECTOR3(300.0f, 0.0f, 300.0f), D3DXVECTOR3(300.0f, 0.0f, -300.0f), TEXT("Image/Surface/ground.png"));

	m_pSide1 = new cSurface();
	m_pSide1->Setup(D3DXVECTOR3 (-300.0f, 0.0f, 300.0f), D3DXVECTOR3 (-300.0f, 300.0f, 300.0f), D3DXVECTOR3(300.0f, 300.0f, 300.0f), D3DXVECTOR3(300.0f, 0.0f, 300.0f), TEXT("Image/Surface/skywall.png"));
	m_pSide2 = new cSurface();
	m_pSide2->Setup(D3DXVECTOR3 (-300.0f, 0.0f, -300.0f), D3DXVECTOR3 (-300.0f, 300.0f, -300.0f), D3DXVECTOR3 (-300.0f, 300.0f, 300.0f), D3DXVECTOR3 (-300.0f, 0.0f, 300.0f), TEXT("Image/Surface/skywall2.png"));
	m_pSide3 = new cSurface();
	m_pSide3->Setup(D3DXVECTOR3(300.0f, 0.0f, -300.0f), D3DXVECTOR3(300.0f, 300.0f, -300.0f), D3DXVECTOR3(-300.0f, 300.0f, -300.0f), D3DXVECTOR3(-300.0f, 0.0f, -300.0f), TEXT("Image/Surface/skywall.png"));
	m_pSide4 = new cSurface();
	m_pSide4->Setup(D3DXVECTOR3(300.0f, 0.0f, 300.0f), D3DXVECTOR3(300.0f, 300.0f, 300.0f), D3DXVECTOR3(300.0f, 300.0f, -300.0f), D3DXVECTOR3(300.0f, 0.0f, -300.0f), TEXT("Image/Surface/skywall2.png"));

	Set_Light();
}

void cPlayScene::Update()
{
	if (m_pCubeMan)
	{
		m_pCubeMan->Update();
		m_pPosToCreateTile->UpdateLocation(m_pCubeMan->GetFrontPos());
	}

	if (m_pCamera) m_pCamera->Update();
}

void cPlayScene::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();


	if (m_pCubeMan) m_pCubeMan->Render();
	if (m_pPosToCreateTile) m_pPosToCreateTile->Render();
	//if (m_pTop) m_pTop->Render();
	if (m_pSide1) m_pSide1->Render();
	if (m_pSide2) m_pSide2->Render();
	if (m_pSide3) m_pSide3->Render();
	if (m_pSide4) m_pSide4->Render();
	if (m_pBottom) m_pBottom->Render();

	g_ObjectManager->Render();
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cPlayScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hwnd, message, wParam, lParam);
	}
}

void cPlayScene::Set_Light()
{
	D3DLIGHT9 stLight;
	{
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		stLight.Type = D3DLIGHT_DIRECTIONAL;
		stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		g_pD3DDevice->SetLight(0, &stLight);
	}

	g_pD3DDevice->LightEnable(0, true);
}
