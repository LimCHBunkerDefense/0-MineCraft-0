#pragma once
class cPyramid
{
public:
	cPyramid();
	~cPyramid();

	/// >> : 3.
private:
	std::vector<ST_PN_VERTEX>	m_vecVertex;	// << : 13 ���� ST_PN_VERTEX
	D3DXMATRIXA16				m_matR;
	D3DMATERIAL9				m_stMtl;	// << : 13.
public:

	void Setup(D3DXCOLOR c, D3DXMATRIXA16& mat);	// << : 13. ���� ����
	void Render();
	/// << : 


};

