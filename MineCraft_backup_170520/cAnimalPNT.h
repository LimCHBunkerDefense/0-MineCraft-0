#pragma once

class cAnimalPNT
{
public:
	cAnimalPNT();
protected:
	std::vector<ST_PNT_VERTEX>	m_vecVertex;

public:
	virtual ~cAnimalPNT();
	virtual	void Setup();
	virtual	void Update();
	virtual	void Render();
};

