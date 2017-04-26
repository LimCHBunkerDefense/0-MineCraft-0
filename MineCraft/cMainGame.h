#pragma once


class cMainGame
{

public:
	cMainGame();
	~cMainGame();

public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

