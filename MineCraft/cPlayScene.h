#pragma once

#include "cSceneManager.h"

class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cSurface;
class cSun;
class cMoon;
class cButton;
class cAnimal;

#define WallLength	500.0f

class cPlayScene : public IScene
{
	cCamera*	m_pCamera;
	cCubeMan*	m_pCubeMan;
	cSurface*	m_pPosToCreateTile;

	// >> : 해와 달
	cSun*		m_pSun;
	cMoon*		m_pMoon;
	int			time;		// 해와 달 움직이는 시간
	// << :

	// >>  : 배경
	cSurface*	m_pTop;
	cSurface*	m_pBottom;
	cSurface*	m_pSide1;
	cSurface*	m_pSide2;
	cSurface*	m_pSide3;
	cSurface*	m_pSide4;
	// << 
	cButton*	m_pButton_Start;

	// << : 동물
	cAnimal*	m_pAnimal;
	cAnimal*	m_pAnimal2;
	cAnimal*	m_pAnimal3;
	cAnimal*	m_pAnimal4;
	std::vector<cAnimal*> m_vecAnimal;
	// >> :

public:
	cPlayScene();
	~cPlayScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
};

