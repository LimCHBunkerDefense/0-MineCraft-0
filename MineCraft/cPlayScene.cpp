#include "stdafx.h"
#include "cPlayScene.h"

#include "cDeviceManager.h"	
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"


cPlayScene::cPlayScene() : 
	m_pCubeMan(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
{
}


cPlayScene::~cPlayScene()
{
	SAFE_DELETE(m_pCubeMan);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	g_pDeviceManager->Destroy();
}

void cPlayScene::Setup()
{
	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());
	
	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	Set_Light();
}

void cPlayScene::Update()
{
	if (m_pCubeMan)	m_pCubeMan->Update();
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


	if (m_pGrid) m_pGrid->Render();
	if (m_pCubeMan) m_pCubeMan->Render();


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
