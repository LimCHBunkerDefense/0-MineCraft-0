#include "stdafx.h"
#include "cLoadingScene.h"
#include "cSurface.h"
#include "cInputManager.h"

cLoadingScene::cLoadingScene()
	: m_pBg(NULL)
	
{
}


cLoadingScene::~cLoadingScene()
{
	SAFE_DELETE(m_pBg);
}


void cLoadingScene::Setup()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/LoadingScene/bg.png"));
}

void cLoadingScene::Update()
{
	if (INPUT->IsKeyDown(VK_F2)) SCENE->ChangeScene(SCENE_TITLE);

}

void cLoadingScene::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	//m_pBg->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cLoadingScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
