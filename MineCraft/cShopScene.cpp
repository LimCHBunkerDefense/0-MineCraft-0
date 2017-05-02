#include "stdafx.h"
#include "cShopScene.h"
#include "cInputManager.h"
#include "cSurface.h"
#include "cButton.h"


cShopScene::cShopScene()
	: m_pBg(NULL)
	, m_pSelectButton(NULL)
{
}


cShopScene::~cShopScene()
{
	SAFE_DELETE(m_pSelectButton);
	SAFE_DELETE(m_pBg);
}

void cShopScene::Setup()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/TitleScene/bg.png"));

	m_pSelectButton = new cButton();
	m_pSelectButton->Setup(D3DXVECTOR3(VIEW_WIDTH * 0.30f, VIEW_HEIGHT * 0.05f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.30f, VIEW_HEIGHT * 0.10f, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.40f, VIEW_HEIGHT * 0.10f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.40f, VIEW_HEIGHT * 0.05f, -0.2f), D3DCOLOR_XRGB(150, 150, 150, 1.0f));
	m_pSelectButton->SetText(("Select"), 40, D3DCOLOR_XRGB(0, 0, 0, 0));
}

void cShopScene::Update()
{
	if (INPUT->IsKeyDown(VK_BACK)) SCENE->ChangeScene(SCENE_TITLE);
}

void cShopScene::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();


	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cShopScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}