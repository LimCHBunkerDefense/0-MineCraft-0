#include "stdafx.h"
#include "cLoadingScene.h"
#include "cCamera.h"
#include "cSurface.h"
#include "cInputManager.h"
#include "cTextureManager.h"

cLoadingScene::cLoadingScene()
	: m_pBg(NULL)
	, m_pCamera(NULL)
	, m_pTexture(NULL)
	, m_point(0.0f, VIEW_HEIGHT * 0.5f, 0.0f)
	
{
}


cLoadingScene::~cLoadingScene()
{
	SAFE_DELETE(m_pBg);
	SAFE_DELETE(m_pCamera);

}


void cLoadingScene::Setup()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/LoadingScene/bg.png"));
	m_pCamera = new cCamera();
	m_pCamera->Setup(&m_point);
	m_pCamera->SetPosition();
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

	m_pBg->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}