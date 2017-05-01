#pragma once

#include "cSceneManager.h"

class cSurface;
class cCamera;

class cTitleScene : public IScene
{
	D3DXVECTOR3 m_point;
	cSurface*	m_pBg;
	cSurface*	m_pLogo;
	cCamera*	m_pCamera;

public:
	cTitleScene();
	~cTitleScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

