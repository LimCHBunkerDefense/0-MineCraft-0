#include "stdafx.h"
#include "cTitleScene.h"
#include "cCamera.h"
#include "cSurface.h"
#include "cButton.h"
#include "cText_2D.h"


cTitleScene::cTitleScene() : 
	m_pBg(NULL),
	m_pLogo(NULL),
	m_pCamera(NULL),
	m_pButton_Start(NULL),
	m_pButton_Shop(NULL),
	m_pButton_Help(NULL),
	m_point(0.0f, VIEW_HEIGHT * 0.5f, 0.0f)
{
	SOUND->LoadFile("TitleBGM", "Sound/Mice on Venus.mp3", true);
	
}


cTitleScene::~cTitleScene()
{

}


void cTitleScene::OnEnter()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F),TEXT("Image/TitleScene/bg.png"), false);

	m_pLogo = new cSurface();
	m_pLogo->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.7f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.7f, -0.1f), TEXT("Image/TitleScene/logo.png"), false);
	m_pLogo->SetisThisLogo();

	m_pCamera = new cCamera();
	m_pCamera->Setup(&m_point);
	m_pCamera->SetPosition();

	m_pButton_Start = new cButton();
	m_pButton_Start->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.40f, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.52f, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.52f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.40f, -0.2f), D3DCOLOR_XRGB(150, 150, 150, 1.0f));

	
	RECT rect;
	SetRect(&rect, 475, 375, 975, 429);
	m_pButton_Start->SetText("P L A Y", rect,50);

	m_pButton_Shop = new cButton();
	m_pButton_Shop->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.25, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.37, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.37, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.25, -0.2f), D3DCOLOR_XRGB(150, 150, 150, 1.0f));
	SetRect(&rect, 465, 485, 965, 539);
	m_pButton_Shop->SetText("S H O P", rect, 50);
	
	
	m_pButton_Help = new cButton();
	m_pButton_Help->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.35F, VIEW_HEIGHT * 0.2F, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.35F, VIEW_HEIGHT * 0.27F, -0.2F),
		D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.27F, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.2F, -0.2F), D3DCOLOR_XRGB(150, 150, 150, 1.0f));

	
	
	
	SOUND->Play("TitleBGM", 0.5f);
}

void cTitleScene::OnUpdate()
{
	//if (INPUT->IsKeyDown(VK_F7)) SCENE->ChangeScene(SCENE_LOADING);
	if (m_pButton_Start->IsClicked())
	{
		SCENE->ChangeScene(SCENE_PLAY);
		SOUND->Stop("TitleBGM");
	}

	if (m_pButton_Shop->IsClicked()) SCENE->ChangeScene(SCENE_SHOP);
	if (m_pButton_Help->IsClicked()) OnHelp();
	if (m_pButton_Start) m_pButton_Start->Update();
	if (m_pButton_Shop) m_pButton_Shop->Update();
	if (m_pButton_Help) m_pButton_Help->Update();
}

void cTitleScene::OnDraw()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);
	
	g_pD3DDevice->BeginScene();
	
	m_pBg->Render();
	
	m_pLogo->Render();
	
	m_pButton_Start->Render();
	m_pButton_Shop->Render();

	//도움말버튼
	m_pButton_Help->Render();

	g_pD3DDevice->EndScene();
	
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cTitleScene::OnExit()
{
	SAFE_DELETE(m_pBg);
	SAFE_DELETE(m_pLogo);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pButton_Start);
	SAFE_DELETE(m_pButton_Shop);
	SAFE_DELETE(m_pButton_Help);
}

void cTitleScene::OnHelp()
{
	//도움말 창 만들것.
}


void cTitleScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

}
