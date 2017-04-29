#pragma once

#include "cSceneManager.h"

class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cSurface;


class cPlayScene : public IScene
{
	cCamera*	m_pCamera;
	cCubeMan*	m_pCubeMan;
	cSurface*	m_surface1;
	cSurface*	m_surface2;
	cSurface*	m_surface3;
	cSurface*	m_surface4;


public:
	cPlayScene();
	~cPlayScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
};

