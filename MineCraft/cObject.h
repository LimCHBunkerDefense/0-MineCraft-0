#pragma once
#include "cCubePNT.h"
class cObject :
	public cCubePNT
{
protected:
	D3DXVECTOR3		m_vLocalPos;
	D3DXMATRIXA16	m_matLocalTM;
	OBJECT_NAME     m_name;
public:
	cObject();
	cObject(D3DXVECTOR3 pos);
	~cObject();
	D3DXVECTOR3 GetPosition() { return m_vLocalPos; }
	void        SetName(OBJECT_NAME name) { m_name = name; }
	OBJECT_NAME GetName() { return m_name; }
	void        SetDirtTexture();

	virtual void Setup() {};
	virtual void Render();
};

