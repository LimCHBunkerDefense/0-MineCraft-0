#pragma once

#include "cSceneManager.h"

class GSprite;

class cTitleScene : public IScene
{
public:
	cTitleScene();
	~cTitleScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

