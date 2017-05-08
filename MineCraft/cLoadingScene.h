#pragma once
#include "cSceneManager.h"

class cSurface;
class cCamera;


class cLoadingScene : public IScene
{
	cSurface*	m_pBg;
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

