#pragma once

#include "cSceneManager.h"

class cSurface;

class cTitleScene : public IScene
{
	cSurface* m_Bg;
public:
	cTitleScene();
	~cTitleScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

