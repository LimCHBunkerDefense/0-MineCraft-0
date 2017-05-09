#pragma once
class cAnimal
{
public:
	cAnimal();
protected:
	float	m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;

public:
	int nMoveCount;
	int nRotationCount;
	int nRandCount;

	int nRandRotation;

	bool IsRotation;
	bool IsMove;

	// >> : 조종행동을 위해 생성
	D3DXVECTOR3		m_prevPosition;
	D3DXVECTOR3		m_vTargetPos;

	D3DXVECTOR3     SetTargetPos();
	// << :
	virtual ~cAnimal();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual D3DXVECTOR3 & GetPosition();

};

