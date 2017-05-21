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
class cAnimal;

#define WallLength	500.0f

class cPlayScene : public IScene
{
	cCamera*	m_pCamera;
	cCubeMan*	m_pCubeMan;
	cSurface*	m_pPosToCreateTile;

	// >> : �ؿ� ��
	cSun*		m_pSun;
	cMoon*		m_pMoon;
	int			time;		// �ؿ� �� �����̴� �ð�
	// << :

	cButton*	m_pButton_Start;


	// <<: 2D �ؽ������
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DTEXTURE9 m_pSelTexture;
	D3DXVECTOR3 m_pTexturePos;

	// >>

	// << : ����
	cAnimal*	m_pAnimal;
	cAnimal*	m_pAnimal2;
	cAnimal*	m_pAnimal3;
	cAnimal*	m_pAnimal4;
	std::vector<cAnimal*> m_vecAnimal;
	// >> :

public:
	cPlayScene();
	~cPlayScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnDraw();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Light();
	D3DXCOLOR SkyColor();
	D3DXCOLOR ColorLerp(float startAngle, float endAngle, float currentAngle, D3DXCOLOR startColor, D3DXCOLOR endColor);
	void SetPlayerSkin();
	void SetCamera();
	void UISkillbar();
};

