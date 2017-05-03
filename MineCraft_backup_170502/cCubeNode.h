#pragma once
#include "cCubePNT.h"

class cCubeNode : public cCubePNT
{
public:
	cCubeNode();
	
protected :
	D3DXVECTOR3		m_vLocalPos; 
	D3DXMATRIXA16	m_matLocalTM; 
	D3DXMATRIXA16	m_matWorldTM;
	std::vector<cCubeNode*> m_vecChild; 

	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);
	SYNTHESIZE(float, m_fRotX, RotX);

public :
	virtual ~cCubeNode();

	virtual void AddChild(cCubeNode* pChild); 
	virtual void RotateRotX();
	virtual void SetDefaultRotX();
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

