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
#include "cAnimalMan.h"

// x , y , z
#define DEFAULT_TAXTURE_POS 325.0f, 650.0f, 0.0f

cPlayScene::cPlayScene()
	: m_pCubeMan(NULL)
	, m_pCamera(NULL)
	, m_pSun(NULL)
	, m_pMoon(NULL)
	, m_pPosToCreateTile(NULL)
	, time(NULL)
	, m_pButton_Start(NULL)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pSelTexture(NULL)
	, m_pTexturePos(325.0f, 650.0f, 0.0f)
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
	if (g_ObjectManager->GetVecObject().empty())
	{
		float x = -100.0f;
		float z = -100.0f;
		for (int i = 0; i < 40000; i++)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(x, -1.0f, z);
			g_ObjectManager->CreateObject(pos, OBJECT_DIRT);
			x += 1.0f;
			if (x >= 100.0f)
			{
				z += 1.0f;
				x = -100.0f;
			}
		}
	}
	g_ObjectManager->CreateObject(D3DXVECTOR3(0.5f, 0.0f, 0.5f), OBJECT_DIRT);
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

	// << : Sprite 생성 및 텍스쳐 이미지 불러오기
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar.png", &m_pTexture);
	//D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar.png", &m_pSelTexture);
	// <<
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

	// >> : 동물
	for (int i = 0; i < m_vecAnimal.size(); i++)
	{
		m_vecAnimal[i]->Update();
	}
	// << :

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

	g_ObjectManager->ClearNearVec();
	//GravityUpdate(m_pBottom->GetVerTex());


	// >> 카메라 시작
	if (m_pCamera) 
	{
		SetCamera();
		switch (m_pCamera->GetCamIndex())
		{
		case CAMERA_1:
			m_pCamera->Update();
			break;
		case CAMERA_2:
			m_pCamera->Update2(m_pCubeMan->GetDirection());
			break;
		}
	}
	// << 카메라 끝
}

void cPlayScene::OnDraw()
{
	//D3DCOLOR_RGBA((int)SkyColor().r, (int)SkyColor().r,(int)SkyColor().r, (int)SkyColor().r);
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_RGBA((int)SkyColor().r, (int)SkyColor().g, (int)SkyColor().b, (int)SkyColor().a),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// Set_Light();

	g_ObjectManager->Render(m_pCubeMan->GetPosition());
	if (m_pCubeMan) m_pCubeMan->Render();
	if (m_pPosToCreateTile) m_pPosToCreateTile->Render();

	// >> : 해와 달 Render
	if (m_pSun)	m_pSun->Render();
	else if (m_pMoon) m_pMoon->Render();
	// << :
	// << : UI Render
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(m_pTexture, NULL, NULL, &D3DXVECTOR3(DEFAULT_TAXTURE_POS), D3DCOLOR_ARGB(255, 255, 255, 255));
	UISkillbar();
	if (m_pCubeMan->GetCurrentObjState() != OBJECT_NONE)
	{
		m_pSprite->Draw(m_pSelTexture, NULL, NULL, &m_pTexturePos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_pSprite->End();
	// >>
	//g_ObjectManager->Render();
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

	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSelTexture);

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
	if (INPUT->IsKeyDown('C'))
	{
		m_pCamera->SetCamIndex();
		m_pCubeMan->SetMouseOn();
	}
}

void cPlayScene::UISkillbar()
{
	if (INPUT->IsKeyPress(VK_1))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel01.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(DEFAULT_TAXTURE_POS);
	}

	else if (INPUT->IsKeyPress(VK_2))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel02.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(380.0f, 650.0f, 0.0f);
	}

	else if (INPUT->IsKeyPress(VK_3))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel03.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(437.0f, 650.0f, 0.0f);
	}

	else if (INPUT->IsKeyPress(VK_4))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel04.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(494.0f, 650.0f, 0.0f);
	}

	else if (INPUT->IsKeyPress(VK_5))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel05.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(550.0f, 650.0f, 0.0f);
	}

	else if (INPUT->IsKeyPress(VK_6))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(605.0f, 650.0f, 0.0f);
	}

	else if (INPUT->IsKeyPress(VK_7))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(660.0f, 650.0f, 0.0f);
	}

	else if (INPUT->IsKeyPress(VK_8))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(717.0f, 650.0f, 0.0f);
	}

	else if (INPUT->IsKeyPress(VK_9))
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/UI/GUI_Skill_Bar_Sel.png", &m_pSelTexture);
		m_pTexturePos = D3DXVECTOR3(774.0f, 650.0f, 0.0f);
	}
}

D3DXCOLOR cPlayScene::SkyColor()
{
	if (m_pSun)
	{
		D3DXVECTOR2 vLeft = D3DXVECTOR2(-1, 0);
		D3DXVECTOR2 vPosition = D3DXVECTOR2(m_pSun->GetPosition().x, m_pSun->GetPosition().y);
		D3DXVec2Normalize(&vPosition, &vPosition);

		float cosTheta = D3DXVec2Dot(&vLeft, &vPosition);
		if (acosf(cosTheta) < D3DX_PI / 2.0f)
		{
			return D3DXCOLOR(136, 206, 235, 1.0f);
		}
		else if (acosf(cosTheta) >= D3DX_PI / 2.0f && acosf(cosTheta) < (D3DX_PI / 2.0f + D3DX_PI / 4.0f))
		{
			return ColorLerp(D3DX_PI / 2.0f, D3DX_PI / 2.0 + D3DX_PI / 4.0f, acosf(cosTheta), D3DXCOLOR(136, 206, 235, 1.0f), D3DXCOLOR(253, 255, 49, 0.8f));
		}
		else if (acosf(cosTheta) >= (D3DX_PI / 2.0f + D3DX_PI / 4.0f))
		{
			return ColorLerp(D3DX_PI / 2.0f, D3DX_PI / 2.0 + D3DX_PI / 4.0f, acosf(cosTheta), D3DXCOLOR(253, 255, 49, 0.8f), D3DXCOLOR(252, 163, 53, 0.8f));
		}

	}
	else if (m_pMoon)
	{
		return D3DXCOLOR(30, 73, 171, 1.0f);
	}


}

D3DXCOLOR cPlayScene::ColorLerp(float startAngle, float endAngle, float currentAngle, D3DXCOLOR startColor, D3DXCOLOR endColor)
{
	float deltaAngle = (currentAngle - startAngle) / (endAngle - startAngle);
	float deltaColorR = endColor.r - startColor.r;
	float deltaColorG = endColor.g - startColor.g;
	float deltaColorB = endColor.b - startColor.b;

	return startColor + D3DXCOLOR(deltaAngle * deltaColorR, deltaAngle * deltaColorG, deltaAngle * deltaColorB, 1.0f);
}