#pragma once
#include "cSceneManager.h"
class cSurface;
class cCamera;
class cTextureManager;


class cLoadingScene : public IScene
{
	D3DXVECTOR3 m_point;
	cSurface*	m_pBg;
	cCamera*	m_pCamera;
	cTextureManager* m_pTexture;

public:
	cLoadingScene();
	~cLoadingScene();

	void Setup();
	void Update();
	void Render();

};

