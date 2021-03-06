#include "stdafx.h"
#include "cAnimalNose.h"


cAnimalNose::cAnimalNose()
{
}


cAnimalNose::~cAnimalNose()
{
}

void cAnimalNose::Setup()
{
	cAnimalNode::Setup();

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.1f, 0.05f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS*matT;

	{
		m_vecVertex[0].t.x = (float)17 / 64;	m_vecVertex[0].t.y = (float)17 / 32;
		m_vecVertex[1].t.x = (float)17 / 64;	m_vecVertex[1].t.y = (float)20 / 32;
		m_vecVertex[2].t.x = (float)21 / 64;	m_vecVertex[2].t.y = (float)20 / 32;	 //�ո� ���ﰢ 
																					 //0,1,2

		m_vecVertex[3].t.x = (float)17 / 64;	m_vecVertex[3].t.y = (float)17 / 32;
		m_vecVertex[4].t.x = (float)21 / 64;	m_vecVertex[4].t.y = (float)20 / 32;
		m_vecVertex[5].t.x = (float)21 / 64;	m_vecVertex[5].t.y = (float)17 / 32;	 //�ո� �Ʒ��ﰢ
																					 //0,2,3

		m_vecVertex[6].t.x = (float)3 / 64;	m_vecVertex[6].t.y = (float)13 / 32;
		m_vecVertex[7].t.x = (float)4 / 64;	m_vecVertex[7].t.y = (float)10 / 32;
		m_vecVertex[8].t.x = (float)3 / 64;	m_vecVertex[8].t.y = (float)10 / 32;	 //�޸� ���ﰢ
																					 //4,6,5
		m_vecVertex[9].t.x = (float)3 / 64;	m_vecVertex[9].t.y = (float)13 / 32;
		m_vecVertex[10].t.x = (float)4 / 64; m_vecVertex[10].t.y = (float)13 / 32;
		m_vecVertex[11].t.x = (float)4 / 64; m_vecVertex[11].t.y = (float)10 / 32;	 //�޸� �Ʒ��ﰢ
																					 //4,7,6

		m_vecVertex[12].t.x = (float)0 / 64;	m_vecVertex[12].t.y = (float)13 / 32;
		m_vecVertex[13].t.x = (float)0 / 64;	m_vecVertex[13].t.y = (float)10 / 32;
		m_vecVertex[14].t.x = (float)1 / 64;	m_vecVertex[14].t.y = (float)10 / 32;	 //���ʸ� ���ﰢ
																						 //4,5,1

		m_vecVertex[15].t.x = (float)0 / 64;	m_vecVertex[15].t.y = (float)13 / 32;
		m_vecVertex[16].t.x = (float)1 / 64;	m_vecVertex[16].t.y = (float)10 / 32;
		m_vecVertex[17].t.x = (float)1 / 64;	m_vecVertex[17].t.y = (float)13 / 32;	 //���ʸ� �Ʒ��ﰢ
																						 //4,1,0

		m_vecVertex[18].t.x = (float)2 / 64;	m_vecVertex[18].t.y = (float)13 / 32;
		m_vecVertex[19].t.x = (float)2 / 64;	m_vecVertex[19].t.y = (float)10 / 32;
		m_vecVertex[20].t.x = (float)3 / 64;	m_vecVertex[20].t.y = (float)10 / 32;	 //������ ���ﰢ
																						 //3,2,6

		m_vecVertex[21].t.x = (float)2 / 64;	m_vecVertex[21].t.y = (float)13 / 32;
		m_vecVertex[22].t.x = (float)3 / 64;	m_vecVertex[22].t.y = (float)10 / 32;
		m_vecVertex[23].t.x = (float)3 / 64;	m_vecVertex[23].t.y = (float)13 / 32;	 //������ �Ʒ��ﰢ
																						 //3,6,7

		m_vecVertex[24].t.x = (float)1 / 64;	m_vecVertex[24].t.y = (float)10 / 32;
		m_vecVertex[25].t.x = (float)1 / 64;	m_vecVertex[25].t.y = (float)8 / 32;
		m_vecVertex[26].t.x = (float)2 / 64;	m_vecVertex[26].t.y = (float)8 / 32;	 //���� ���ﰢ
																						 //1,5,6

		m_vecVertex[27].t.x = (float)1 / 64;	m_vecVertex[27].t.y = (float)10 / 32;
		m_vecVertex[28].t.x = (float)2 / 64;	m_vecVertex[28].t.y = (float)8 / 32;
		m_vecVertex[29].t.x = (float)2 / 64;	m_vecVertex[29].t.y = (float)10 / 32;	 //���� �Ʒ��ﰢ
																						 //1,6,2

		m_vecVertex[30].t.x = (float)3 / 64;	m_vecVertex[30].t.y = (float)10 / 32;
		m_vecVertex[31].t.x = (float)3 / 64;	m_vecVertex[31].t.y = (float)8 / 32;
		m_vecVertex[32].t.x = (float)2 / 64;	m_vecVertex[32].t.y = (float)8 / 32;	 //�Ʒ��� ���ﰢ
																						 //4,0,3

		m_vecVertex[33].t.x = (float)3 / 64;	m_vecVertex[33].t.y = (float)10 / 32;
		m_vecVertex[34].t.x = (float)2 / 64;	m_vecVertex[34].t.y = (float)8 / 32;
		m_vecVertex[35].t.x = (float)2 / 64;	    m_vecVertex[35].t.y = (float)10 / 32;	 //�Ʒ��� �Ʒ��ﰢ



	}

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPos.z = -0.6f;
}