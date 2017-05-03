#include "stdafx.h"
#include "cTitleScene.h"
#include "cCamera.h"
#include "cSurface.h"
#include "cButton.h"


cTitleScene::cTitleScene() : 
	m_pBg(NULL),
	m_pLogo(NULL),
	m_pCamera(NULL),
	m_pButton_Start(NULL),
	m_pButton_Shop(NULL),
	m_point(0.0f, VIEW_HEIGHT * 0.5f, 0.0f)
{
}


cTitleScene::~cTitleScene()
{
	SAFE_DELETE(m_pBg);
	SAFE_DELETE(m_pLogo);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pButton_Start);
	SAFE_DELETE(m_pButton_Shop);
}


void cTitleScene::Setup()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F),TEXT("Image/TitleScene/bg.png"));

	m_pLogo = new cSurface();
	m_pLogo->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.7f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.7f, -0.1f), TEXT("Image/TitleScene/logo.png"));
	m_pLogo->SetisThisLogo();

	m_pCamera = new cCamera();
	m_pCamera->Setup(&m_point);
	m_pCamera->SetPosition();

	m_pButton_Start = new cButton();
	m_pButton_Start->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.40f, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.52f, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.52f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.40f, -0.2f), D3DCOLOR_XRGB(150, 150, 150, 1.0f));
	m_pButton_Start->SetText(LPCWSTR(TEXT(" P L A Y ")), D3DXVECTOR3(-130, 320, -0.2f), D3DXVECTOR3(80, 80, 80) );

	m_pButton_Shop = new cButton();
	m_pButton_Shop->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.25, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.37, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.37, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.15F, VIEW_HEIGHT * 0.25, -0.2f), D3DCOLOR_XRGB(150, 150, 150, 1.0f));
	m_pButton_Shop->SetText(LPCWSTR(TEXT(" S H O P ")), D3DXVECTOR3(-130, 200, -0.2f), D3DXVECTOR3(80, 80, 80) );

}

void cTitleScene::Update()
{
	if (m_pButton_Start->IsClicked()) SCENE->ChangeScene(SCENE_PLAY);
	if (m_pButton_Shop->IsClicked()) SCENE->ChangeScene(SCENE_SHOP);
	if (m_pButton_Start) m_pButton_Start->Update();
	if (m_pButton_Shop) m_pButton_Shop->Update();
}

void cTitleScene::Render()
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


	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cTitleScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
