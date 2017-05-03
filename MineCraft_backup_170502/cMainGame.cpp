#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"	
#include "cSceneManager.h"
#include "cPlayScene.h"
#include "cTitleScene.h"
#include "cShopScene.h"
#include "cInputManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"



cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Setup()
{
	INPUT->Setup();
	SCENE->Register(SCENE_TITLE, new cTitleScene);
	SCENE->Register(SCENE_PLAY, new cPlayScene);
	SCENE->Register(SCENE_SHOP, new cShopScene);
	SCENE->ChangeScene(SCENE_TITLE);
}

void cMainGame::Update()
{
	SCENE->Update();
	INPUT->Update();
}

void cMainGame::Render()
{
	SCENE->Render();
}

void cMainGame::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SCENE->WndProc(hwnd, message, wParam, lParam);
}