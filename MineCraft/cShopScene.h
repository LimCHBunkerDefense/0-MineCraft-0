#pragma once

#include "cSceneManager.h"

class cShopScene : public IScene
{
public:
	cShopScene();
	~cShopScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

