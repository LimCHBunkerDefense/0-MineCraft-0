#include "stdafx.h"
#include "cTitleScene.h"
#include "cSurface.h"


cTitleScene::cTitleScene() : 
	m_Bg(NULL)
{
}


cTitleScene::~cTitleScene()
{
	SAFE_DELETE(m_Bg);
}


void cTitleScene::Setup()
{
	m_Bg = new cSurface();
	//m_Bg->Setup(D3DXVECTOR3());
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


	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cTitleScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
