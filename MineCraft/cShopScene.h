#pragma once

#include "cSceneManager.h"

class cSurface;
class cButton;
class cCubeMan;

enum SKIN_INDEX
{
	SKIN_NONE, SKIN_BATMAN, SKIN_CAPTAIN, SKIN_IRON, SKIN_SPIDER,
};

class cShopScene : public IScene
{
	cSurface*	m_pBg;
	cSurface*	m_pGUI_Outline;
	cSurface*	m_pGUI_Inform;

	cButton*	m_pUI_leftButton;
	cButton*	m_pUI_rightButton;
	cButton*	m_pSelectButton;
	cButton*	m_pBackButton;

	int			m_nSkinIndex;
	cCubeMan*	m_pExampleMan01;
	cCubeMan*	m_pExampleMan02;
	cCubeMan*	m_pExampleMan03;
	cCubeMan*	m_pMyMan;

public:
	cShopScene();
	~cShopScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
	void SetupExampleMan();
	void UpdateExampleMan();
	void UpdateExampleSkin();
	void SelectSkin();

	int GetSkinIndex() { return m_nSkinIndex; }
};

