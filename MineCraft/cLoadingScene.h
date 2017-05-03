#pragma once
#include "cSceneManager.h"
class cSurface;


class cLoadingScene : public IScene
{
	cSurface*	m_pBg;
	cSurface*	m_pGageBar;
	cSurface*	m_pGage;

public:
	cLoadingScene();
	~cLoadingScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

