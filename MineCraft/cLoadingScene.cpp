#include "stdafx.h"
#include "cLoadingScene.h"
#include "cSurface.h"
#include "cInputManager.h"
#include "cCamera.h"


cLoadingScene::cLoadingScene()
	: m_pBg(NULL)
	, m_pGageBar(NULL)
	, m_pGage(NULL)
	//, m_pGage2(NULL)
	//, m_pGage3(NULL)
	,m_point(0.0f, VIEW_HEIGHT * 0.5f, 0.0f)
	, m_pCamera(NULL)
{
}


cLoadingScene::~cLoadingScene()
{
	
}


void cLoadingScene::OnEnter()
{
	m_pCamera = new cCamera();
	m_pCamera->Setup(&m_point);
	m_pCamera->SetPosition();

	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/LoadingScene/bg.png"), false);
	
	m_pGage = new cSurface();
	m_pGage->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.8f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(-150.0F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(-150.0F, VIEW_HEIGHT * 0.8f, -0.1f), TEXT("Image/LoadingScene/loading_Gage.png"), false);
	m_pGage->IMG_SetScale(0.5F);

	/*m_pGage2 = new cSurface();
	m_pGage2->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.8f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(-100.0F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(-100.0F, VIEW_HEIGHT * 0.8f, -0.1f), TEXT("Image/LoadingScene/loading_Gage.png"), false);
	m_pGage2->IMG_SetScale(0.5F);

	m_pGage3 = new cSurface();
	m_pGage3->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.8f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(50.0F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(50.0F, VIEW_HEIGHT * 0.8f, -0.1f), TEXT("Image/LoadingScene/loading_Gage.png"), false);
	m_pGage3->IMG_SetScale(0.5F);*/

	m_pGageBar = new cSurface();
	m_pGageBar->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.8f, -0.1f), D3DXVECTOR3(-VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f),
		D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.9f, -0.1f), D3DXVECTOR3(VIEW_WIDTH * 0.3F, VIEW_HEIGHT * 0.8f, -0.1f), TEXT("Image/LoadingScene/loading_bar.png"), false);
	m_pGageBar->IMG_SetScale(0.5F);
}

void cLoadingScene::OnUpdate()
{

}

void cLoadingScene::OnDraw()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();
	m_pBg->Render();
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	OnExit();
}

void cLoadingScene::OnExit()
{
	Sleep(1000);
	SCENE->ChangeScene(SCENE_TITLE);

}

void cLoadingScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
