#include "stdafx.h"
#include "cShopScene.h"
#include "cInputManager.h"
#include "cSurface.h"
#include "cButton.h"


cShopScene::cShopScene()
	: m_pBg(NULL)
	, m_pGUI_Outline(NULL)
	, m_pGUI_In(NULL)
	, m_pSelectButton(NULL)
	, m_pUI_leftButton(NULL)
	, m_pUI_rightButton(NULL)
{
}


cShopScene::~cShopScene()
{

}

void cShopScene::OnEnter()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/TitleScene/bg.png"), false);

	m_pGUI_Outline = new cSurface();
	m_pGUI_Outline->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.1f, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.9f, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.9f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.1f, -0.2f), TEXT("Image/UI/GUI_Outline.png"), false);
	m_pGUI_Outline->SetUI(1.0f, 0.8f);

	m_pGUI_In = new cSurface();
	m_pGUI_In->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.1f, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.9f, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.9f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.1f, -0.2f), TEXT("Image/UI/GUI_In.png"), false);
	m_pGUI_In->SetUI(0.9f, 0.7f);

	m_pUI_leftButton = new cButton();
	m_pUI_leftButton->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.32f, VIEW_HEIGHT * 0.62f, -0.3f), D3DXVECTOR3(-VIEW_WIDTH * 0.32f, VIEW_HEIGHT * 0.72f, -0.3f),
		D3DXVECTOR3(-VIEW_WIDTH * 0.29f, VIEW_HEIGHT * 0.72f, -0.3f), D3DXVECTOR3(-VIEW_WIDTH * 0.29f, VIEW_HEIGHT * 0.62f, -0.3f), D3DCOLOR_XRGB(150, 150, 150, 0.8f));

	m_pUI_rightButton = new cButton();
	m_pUI_rightButton->Setup(D3DXVECTOR3(VIEW_WIDTH * 0.29f, VIEW_HEIGHT * 0.62f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.29f, VIEW_HEIGHT * 0.72f, -0.3f),
		D3DXVECTOR3(VIEW_WIDTH * 0.32f, VIEW_HEIGHT * 0.72f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.32f, VIEW_HEIGHT * 0.62f, -0.3f), D3DCOLOR_XRGB(150, 150, 150, 0.8f));

	m_pSelectButton = new cButton();
	m_pSelectButton->Setup(D3DXVECTOR3(VIEW_WIDTH * 0.13f, VIEW_HEIGHT * 0.26f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.13f, VIEW_HEIGHT * 0.32f, -0.3f),
		D3DXVECTOR3(VIEW_WIDTH * 0.23f, VIEW_HEIGHT * 0.32f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.23f, VIEW_HEIGHT * 0.26f, -0.3f), D3DCOLOR_XRGB(150, 150, 150, 0.8f));
	//m_pSelectButton->SetText(("Select"), 40, D3DCOLOR_XRGB(0, 0, 0, 0));
}

void cShopScene::OnUpdate()
{
	if (INPUT->IsKeyDown(VK_BACK)) SCENE->ChangeScene(SCENE_TITLE);
	if (m_pUI_leftButton)	m_pUI_leftButton->Update();
	if (m_pUI_rightButton)	m_pUI_rightButton->Update();
	if (m_pSelectButton)	m_pSelectButton->Update();
}

void cShopScene::OnDraw()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	m_pBg->Render();
	m_pGUI_In->Render();
	m_pGUI_Outline->Render();

	m_pUI_leftButton->Render();
	m_pUI_rightButton->Render();
	
	m_pSelectButton->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cShopScene::OnExit()
{
	SAFE_DELETE(m_pUI_rightButton);
	SAFE_DELETE(m_pUI_leftButton);
	SAFE_DELETE(m_pSelectButton);
	SAFE_DELETE(m_pGUI_In);
	SAFE_DELETE(m_pGUI_Outline);
	SAFE_DELETE(m_pBg);
}

void cShopScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}