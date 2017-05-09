#pragma once

#include "cAnimal.h"
class cAnimalNode;

class cAnimalMan : public cAnimal
{
public:
	cAnimalMan();
	~cAnimalMan();

public:
	cAnimalNode*	m_pRoot;
	LPDIRECT3DTEXTURE9 m_pTexture;  // << : 
	D3DMATERIAL9		m_stMtl;
	// : 

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	void Set_Material();
	//void Set_Material(); // << : 
};

