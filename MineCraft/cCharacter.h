#pragma once
class cCharacter
{
public:
	cCharacter();
	

protected :
	float	m_fRotY; 
	D3DXVECTOR3		m_vDirection; 
	D3DXVECTOR3		m_vPosition; 
	D3DXMATRIXA16	m_matWorld; 

public :
	virtual ~cCharacter();

	virtual void Setup(); 
	virtual void Update(); 
	virtual void Render(); 

	virtual D3DXVECTOR3 & GetPosition(); 





};

