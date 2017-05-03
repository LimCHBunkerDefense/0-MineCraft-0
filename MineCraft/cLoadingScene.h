#pragma once
#include "cSceneManager.h"

class cSurface;
class cCamera;


class cLoadingScene : public IScene
{
	cSurface*	m_pBg;
	cSurface*	m_pGageBar;
	cSurface*	m_pGage;
	//cSurface*	m_pGage2;
	//cSurface*	m_pGage3;

	D3DXVECTOR3 m_point;
	cCamera*	m_pCamera;



public:
	cLoadingScene();
	~cLoadingScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};

