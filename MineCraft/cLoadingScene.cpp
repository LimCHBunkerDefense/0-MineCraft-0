#include "stdafx.h"
#include "cLoadingScene.h"
#include "cSurface.h"
#include "cInputManager.h"

cLoadingScene::cLoadingScene()
	: m_pBg(NULL)
	, m_pGageBar(NULL)
	, m_pGage(NULL)
{
}


cLoadingScene::~cLoadingScene()
{
	SAFE_DELETE(m_pBg);
	SAFE_DELETE(m_pGageBar);
	SAFE_DELETE(m_pGage);

}


void cLoadingScene::Setup()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/LoadingScene/bg.png"));
	
	m_pGageBar = new cSurface();
	m_pGageBar->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT * 0.8f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT * 0.8f, -0.1f), TEXT("Image/LoadingScene/loading bar.png"));
	m_pGageBar->IMG_SetScale(0.5f);

	m_pGage = new cSurface();
	m_pGage->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT * 0.8f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(-250, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(-250, VIEW_HEIGHT * 0.8f, -0.1f), TEXT("Image/LoadingScene/loading gage.png"));
	m_pGage->IMG_SetScale(0.5f);
}

void cLoadingScene::Update()
{
	if (INPUT->IsKeyDown(VK_F2)) SCENE->ChangeScene(SCENE_TITLE);
}

void cLoadingScene::SceneExit()
{
	SCENE->ChangeScene(SCENE_TITLE);
}

void cLoadingScene::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	m_pBg->Render();
	m_pGage->Render();
	m_pGageBar->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cLoadingScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
