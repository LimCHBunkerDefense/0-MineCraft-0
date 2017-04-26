#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"		/// << : 

// >> :
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cPlayScene.h"


cMainGame::cMainGame() : m_pPlayScene(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayScene);
}

void cMainGame::Setup()
{
	m_pPlayScene = new cPlayScene;
	m_pPlayScene->Setup();
}

void cMainGame::Update()
{
	m_pPlayScene->Update();

}

void cMainGame::Render()
{
	m_pPlayScene->Render();
}

void cMainGame::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pPlayScene->WndProc(hwnd, message, wParam, lParam);
}