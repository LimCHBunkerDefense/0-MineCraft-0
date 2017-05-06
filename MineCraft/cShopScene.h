#pragma once

#include "cSceneManager.h"

class cSurface;
class cButton;
class cCubeMan;
class cMSGBox;

class cShopScene : public IScene
{
	cSurface*	m_pBg;
	cSurface*	m_pGUI_Outline;
	cSurface*	m_pGUI_Inform;

	cButton*	m_pUI_leftButton;
	cButton*	m_pUI_rightButton;
	cButton*	m_pSelectButton;
	cButton*	m_pBackButton;

	int			m_nExampleSkinIndex;
	int			m_nMySkinIndex;
	cCubeMan*	m_pExampleMan01;
	cCubeMan*	m_pExampleMan02;
	cCubeMan*	m_pExampleMan03;
	cCubeMan*	m_pMyMan;
	cMSGBox*	m_pMSGBox;

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
	void SetUIImage();
	void SetButtons();
	void SetMSGBox();
	void RenderMSG();

};

