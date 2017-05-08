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

	// >>  : 배경
	cSurface*	m_pTop;
	cSurface*	m_pBottom;
	cSurface*	m_pSide1;
	cSurface*	m_pSide2;
	cSurface*	m_pSide3;
	cSurface*	m_pSide4;
	// << 
	cButton*	m_pButton_Start;

	// <<: 2D 텍스쳐출력
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DTEXTURE9 m_pSelTexture;
	D3DXVECTOR3 m_pTexturePos;

	// >>

public:
	cPlayScene();
	~cPlayScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();

	void SetPlayerSkin();
	void UISkillbar();
};

