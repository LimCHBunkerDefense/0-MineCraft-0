#pragma once
#include "cCubePNT.h"
class cObject :
	public cCubePNT
{
protected:
	D3DXVECTOR3		m_vLocalPos;
	D3DXMATRIXA16	m_matLocalTM;
	string          m_name;
public:
	cObject();
	cObject(D3DXVECTOR3 pos);
	~cObject();
	D3DXVECTOR3 GetPosition() { return m_vLocalPos; }
	void        SetName(string name) { m_name = name; }
	string      GetName() { return m_name; }
	void        SetDirtTexture();

	virtual void Setup() {};
	virtual void Render();
};

