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
	cSurface*	m_pPosToCreateTile;

	// >>  : ¹è°æ
	cSurface*	m_pTop;
	cSurface*	m_pBottom;
	cSurface*	m_pSide1;
	cSurface*	m_pSide2;
	cSurface*	m_pSide3;
	cSurface*	m_pSide4;
	// << 


public:
	cPlayScene();
	~cPlayScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
};

