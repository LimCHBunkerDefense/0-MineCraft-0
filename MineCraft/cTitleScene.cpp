#include "stdafx.h"
#include "cTitleScene.h"
#include "cCamera.h"
#include "cSurface.h"


cTitleScene::cTitleScene() : 
	m_pBg(NULL),
	m_pLogo(NULL),
	m_pCamera(NULL),
	m_point(0.0f, VIEW_HEIGHT * 0.5f, 0.0f)
{
}


cTitleScene::~cTitleScene()
{
	SAFE_DELETE(m_pBg);
	SAFE_DELETE(m_pLogo);
	SAFE_DELETE(m_pCamera);
}


void cTitleScene::Setup()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F),TEXT("Image/TitleScene/bg.png"));

	m_pLogo = new cSurface();
	m_pLogo->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.7f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.7f, -0.1f), TEXT("Image/TitleScene/logo.png"));

	m_pCamera = new cCamera();
	m_pCamera->Setup(&m_point);
	m_pCamera->SetPosition();

}

void cTitleScene::Update()
{
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

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cTitleScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
