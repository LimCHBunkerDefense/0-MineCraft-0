#pragma once

#include "cSceneManager.h"

class cSurface;
class cCamera;
class cButton;
class cText_2D;

class cTitleScene : public IScene
{
	D3DXVECTOR3 m_point;
	cSurface*	m_pBg;
	cSurface*	m_pLogo;
	cCamera*	m_pCamera;
	cButton*	m_pButton_Start;
	cButton*	m_pButton_Shop;
	cButton*	m_pButton_Help;
public:
	cTitleScene();
	~cTitleScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void OnHelp();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

