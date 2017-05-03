#pragma once
class cCharacter
{
public:
	cCharacter();
	

protected :
	float	m_fRotY; 
	D3DXVECTOR3		m_vDirection; 
	D3DXVECTOR3		m_vPosition; 
	D3DXVECTOR3		m_vFrontPos;
	D3DXMATRIXA16	m_matWorld; 

	bool			m_isMoving;
	bool			m_isJumping;
	bool			m_isAttack;
	
	float			m_fPrevY;
	
public :
	virtual ~cCharacter();

	virtual void Setup(); 
	virtual void Update(); 
	virtual void Render(); 

	virtual D3DXVECTOR3& GetPosition(); 
	virtual D3DXVECTOR3& GetFrontPos();
	virtual D3DXVECTOR3& GetDirection();

	void SetAttackState(bool a);
	void SetJumpingState(bool j);
};

