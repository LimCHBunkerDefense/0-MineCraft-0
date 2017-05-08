#pragma once

#include "cCharacter.h"
class cCubeNode; 

class cCubeMan  : public cCharacter
{
public:
	cCubeMan();
	~cCubeMan();

public :
	cCubeNode*	m_pRoot; 
	LPDIRECT3DTEXTURE9 m_pTexture;  // << : 
	D3DMATERIAL9		m_stMtl; 
	// : 

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	void Set_Material(); // << : 
	virtual void SetScale(float scale);
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void LookAt(D3DXVECTOR2 lookAt);

};

