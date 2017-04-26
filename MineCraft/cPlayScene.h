#pragma once

class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;

class cPlayScene
{
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
	cCubeMan*	m_pCubeMan;

public:
	cPlayScene();
	~cPlayScene();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
};

