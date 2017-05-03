#pragma once

#include "cSceneManager.h"

class cSurface;
class cButton;
class cCubeMan;

enum SKIN_INDEX
{
	SKIN_NONE, SKIN_BATMAN, 
};

class cShopScene : public IScene
{
	cSurface*	m_pBg;
	cSurface*	m_pGUI_Outline;
	cSurface*	m_pGUI_Inform;

	cButton*	m_pUI_leftButton;
	cButton*	m_pUI_rightButton;
	cButton*	m_pSelectButton;

	SKIN_INDEX	m_nSkinIndex;
	cCubeMan*	m_pExampleMan;
	cCubeMan*	m_pMyMan;

public:
	cShopScene();
	~cShopScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
	void UpdateExampleMan();
};

