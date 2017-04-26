#pragma once

class cPlayScene;

class cMainGame
{
	cPlayScene* m_pPlayScene;

public:
	cMainGame();
	~cMainGame();

public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

