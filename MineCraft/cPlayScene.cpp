#include "stdafx.h"
#include "cPlayScene.h"
#include "cObjectManager.h"
#include "cDeviceManager.h"	
#include "cTextureManager.h"
#include "cObjectManager.h"
#include "cObject.h"
#include "cInputManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cSurface.h"
#include "cSun.h"
#include "cMoon.h"


cPlayScene::cPlayScene() :
	m_pCubeMan(NULL),
	m_pCamera(NULL),
	m_pSun(NULL),
	m_pMoon(NULL),
	m_pPosToCreateTile(NULL)
{
	SOUND->LoadFile("PlayBGM", "Sound/Beginning_Beta.mp3", true);
}


cPlayScene::~cPlayScene()
{

}

void cPlayScene::OnEnter()
{
	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();
	SetPlayerSkin();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	m_pSun = new cSun();
	m_pSun->Setup();

	m_pMoon = new cMoon();
	// m_pMoon->Setup();

	m_pPosToCreateTile = new cSurface();
	m_pPosToCreateTile->Setup(D3DXVECTOR3(-1.0f, 0.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, -1.0f), TEXT("Image/Surface/yellow.png"), false);

	Set_Light();
	//if (g_ObjectManager->GetVecObject().empty())
	//{
	//	float x = -500.0f;
	//	float z = -500.0f;
	//	for (int i = 0; i < 1000000; i++)
	//	{
	//		D3DXVECTOR3 pos = D3DXVECTOR3(x, -1.0f, z);
	//		g_ObjectManager->CreateObject(pos, OBJECT_DIRT);
	//		x += 1.0f;
	//		if (x >= 500.0f)
	//		{
	//			z += 1.0f;
	//			x = -500.0f;
	//		}
	//	}
	//}
	//g_ObjectManager->CreateObject(D3DXVECTOR3(0.5f, 0.0f, 0.5f), OBJECT_DIRT);
	if (SOUND->FindChannel("PlayBGM") == NULL) SOUND->Play("PlayBGM", 10.0f);
}


void cPlayScene::OnUpdate()
{
	if (INPUT->IsKeyDown(VK_BACK)) SCENE->ChangeScene(SCENE_TITLE);
	g_ObjectManager->UpdateVector(m_pCubeMan->GetPosition());
	if (m_pCubeMan)
	{
		m_pCubeMan->Update();
		m_pPosToCreateTile->UpdateLocation(m_pCubeMan->GetFrontPos());
	}
	

	if (m_pCamera) m_pCamera->Update();

	{
		if (time / 10 == 1 || time == 0)
		{
			if (m_pSun)		m_pSun->Update();
			if (m_pSun && m_pSun->GetPosition().y < 0)
			{
				SAFE_DELETE(m_pSun);
				m_pMoon = new cMoon;
				m_pMoon->Setup();
			}

			if (m_pMoon) m_pMoon->Update();
			if (m_pMoon && m_pMoon->GetPosition().y < 0)
			{
				SAFE_DELETE(m_pMoon);
				m_pSun = new cSun;
				m_pSun->Setup();
			}
			time = 0;
		}
		time += 1;
	}

	g_ObjectManager->ClearNearVec();
	//GravityUpdate(m_pBottom->GetVerTex());
}

void cPlayScene::OnDraw()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(120, 164, 253),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	//Set_Light();
	
	g_ObjectManager->Render(m_pCubeMan->GetPosition());
	if (m_pCubeMan) m_pCubeMan->Render();
	if (m_pPosToCreateTile) m_pPosToCreateTile->Render();

	// >> : ÇØ¿Í ´Þ Render
	if (m_pSun)	m_pSun->Render();
	else if (m_pMoon) m_pMoon->Render();
	// << :
	
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cPlayScene::OnExit()
{
	m_pCubeMan->SetTexture(NULL);
	SAFE_DELETE(m_pCubeMan);
	SAFE_DELETE(m_pSun);
	SAFE_DELETE(m_pMoon);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPosToCreateTile);

	SOUND->Stop("PlayBGM");
}

void cPlayScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hwnd, message, wParam, lParam);
	}

	if (m_pCubeMan)
	{
		if (message == WM_LBUTTONDOWN)
		{
			m_pCubeMan->SetAttackState(true);
		}
		if (message == WM_LBUTTONUP)
		{
			m_pCubeMan->SetAttackState(false);
		}
	}
}

void cPlayScene::Set_Light()
{
	D3DLIGHT9 stLight;
	{
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		stLight.Type = D3DLIGHT_DIRECTIONAL;
		stLight.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		stLight.Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		D3DXVECTOR3 vDir(1.0f, -1.0f, -1.0f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		g_pD3DDevice->SetLight(0, &stLight);
	}

	g_pD3DDevice->LightEnable(0, true);
}

void cPlayScene::SetPlayerSkin()
{
	int index = SCENE->GetSkinIndex();

	switch (index)
	{
	case SKIN_BATMAN:
		m_pCubeMan->SetTexture(g_pTextureManager->GetTexture(SKIN_BATMAN));
		break;
	case SKIN_CAPTAIN:
		m_pCubeMan->SetTexture(g_pTextureManager->GetTexture(SKIN_CAPTAIN));
		break;
	case SKIN_IRON:
		m_pCubeMan->SetTexture(g_pTextureManager->GetTexture(SKIN_IRON));
		break;
	case SKIN_SPIDER:
		m_pCubeMan->SetTexture(g_pTextureManager->GetTexture(SKIN_SPIDER));
		break;
	}
}

void cPlayScene::SetCamera()
{
	if (INPUT->IsKeyDown('-'))
	{

	}
}