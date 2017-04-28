#include "stdafx.h"
#include "cShopScene.h"


cShopScene::cShopScene()
{
}


cShopScene::~cShopScene()
{
}

void cShopScene::Setup()
{

}

void cShopScene::Update()
{

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