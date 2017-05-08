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



public:
	cPlayScene();
	~cPlayScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
	D3DXCOLOR& SkyColor();
	D3DXCOLOR ColorLerp(float startAngle, float endAngle, float currentAngle, D3DXCOLOR startColor, D3DXCOLOR endColor);

	void SetPlayerSkin();
	void SetCamera();
};

