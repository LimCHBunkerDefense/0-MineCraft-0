#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"	
#include "cSceneManager.h"
#include "cLoadingScene.h"
#include "cTitleScene.h"
#include "cPlayScene.h"
#include "cShopScene.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"



cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
	SOUND->Release();
}

void cMainGame::Setup()
{
	INPUT->Setup();
	SOUND->Setup();
	SCENE->Register(SCENE_LOADING, new cLoadingScene);
	SCENE->Register(SCENE_TITLE, new cTitleScene);
	SCENE->Register(SCENE_PLAY, new cPlayScene);
	SCENE->Register(SCENE_SHOP, new cShopScene);
	SCENE->ChangeScene(SCENE_TITLE);
}

void cMainGame::Update()
{
	SCENE->Update();
	SOUND->Update();
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