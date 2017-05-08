#pragma once

enum CHARACTER_TAG
{
	CHARACTER_NONE, CHARACTER_PLAYER, CHARACTER_EXAMPLE, CHARACTER_MY, 
};

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

	float			m_fScale;
	CHARACTER_TAG	m_tag;
	OBJECT_NAME     m_currentObjName;

	bool			m_isJumping;
	bool			m_isAttack;
	
	float			m_fPrevY;
	
public :
	virtual ~cCharacter();

	virtual void Setup(); 
	virtual void Update(); 
	virtual void Render(); 

	virtual D3DXVECTOR3& GetPosition(); 
	virtual void SetPosition(float x, float y, float z);
	virtual D3DXVECTOR3& GetFrontPos();
	virtual D3DXVECTOR3& GetDirection();
	virtual void SetScale(float scale);
	virtual float GetRotY() { return m_fRotY; }
	virtual void SetRotY(float rotY);
	virtual void SetTag(CHARACTER_TAG tag);

	void SetAttackState(bool a);
	void SetJumpingState(bool j);
};

