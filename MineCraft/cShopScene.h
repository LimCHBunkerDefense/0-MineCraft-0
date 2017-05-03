#pragma once

#include "cSceneManager.h"

class cSurface;
class cButton;

class cShopScene : public IScene
{
	cSurface*	m_pBg;
	cSurface*	m_pGUI_Outline;
	cSurface*	m_pGUI_In;

	cButton*	m_pUI_leftButton;
	cButton*	m_pUI_rightButton;
	cButton*	m_pSelectButton;

public:
	cShopScene();
	~cShopScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

