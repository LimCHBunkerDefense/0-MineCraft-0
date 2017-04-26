#pragma once

// >> : 
class cCubePC;
class cCamera;
class cGrid;
// << : 
class cCubeMan;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	// >> :
private:

public:
	void Setup();
	void Update();
	void Render();
	// << :

	// >> : 
private:
	//cCubePC*	m_pCubePC; 
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
	cCubeMan*	m_pCubeMan;

	// >> : 
	LPDIRECT3DTEXTURE9	 m_pTexture;
	std::vector<ST_PT_VERTEX> m_vecVertex;
	// << : 

public:
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
	// << : 
};

