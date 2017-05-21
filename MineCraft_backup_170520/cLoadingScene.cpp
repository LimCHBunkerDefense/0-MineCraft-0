#include "stdafx.h"
#include "cLoadingScene.h"
#include "cSurface.h"
#include "cInputManager.h"
#include "cCamera.h"

// x , y , z
#define DEFAULT_IMG_SCALE 0.55f, 0.73f, 0.0f

cLoadingScene::cLoadingScene()
	: /*m_pBg(NULL)
	,m_point(0.0f, VIEW_HEIGHT * 0.5f, 0.0f)
	, m_pCamera(NULL)*/
	m_BgSprite(NULL)
	, m_pBgTexture(NULL)
{
}


cLoadingScene::~cLoadingScene()
{
	//SAFE_DELETE(m_pBg);
	//SAFE_DELETE(m_pBg);
	//SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_BgSprite);
	SAFE_DELETE(m_pBgTexture);
}


void cLoadingScene::OnEnter()
{

	D3DXCreateSprite(g_pD3DDevice, &m_BgSprite);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Image/LoadingScene/bg.png", &m_pBgTexture);

	//m_pCamera = new cCamera();
	//m_pCamera->Setup(&m_point);
	//m_pCamera->SetPosition();

	//m_pBg = new cSurface();
	//m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
	//	D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/LoadingScene/bg.png"), false);
	//
}

void cLoadingScene::OnUpdate()
{

}

void cLoadingScene::OnDraw()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pD3DDevice->BeginScene();
	m_BgSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, DEFAULT_IMG_SCALE);
	m_BgSprite->SetTransform(&matS);
	m_BgSprite->Draw(m_pBgTexture, NULL, NULL, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_ARGB(255, 255, 255, 255));
	m_BgSprite->End();
	//m_pBg->Render();
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	OnExit();
}

void cLoadingScene::OnExit()
{
	SCENE->ChangeScene(SCENE_TITLE);
	Sleep(1000);
}

void cLoadingScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
