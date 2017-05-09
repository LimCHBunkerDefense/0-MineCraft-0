#pragma once
#include "cAnimalPNT.h"

class cAnimalNode : public cAnimalPNT
{
public:
	cAnimalNode();

protected:
	float			m_fRotX; // : 
	D3DXVECTOR3		m_vLocalPos;
	D3DXMATRIXA16	m_matLocalTM;
	D3DXMATRIXA16	m_matWorldTM;
	std::vector<cAnimalNode*> m_vecChild;
	
	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);

public:
	virtual ~cAnimalNode();

	virtual void AddChild(cAnimalNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

