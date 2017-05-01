#include "stdafx.h"
#include "cMoon.h"

cMoon::cMoon()
	: m_vPosition(0, 0, 0)
{
}

cMoon::~cMoon()
{
}

void cMoon::Setup()
{

}

void cMoon::Update()
{

}

void cMoon::Render()
{

}

D3DXVECTOR3& cMoon::GetPosition()
{
	return m_vPosition;
}

void cMoon::Set_Material()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �ֺ��� : ������ ������ ������ �ʰ� ����
	m_stMtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���ݻ籤 : Ư�� �������� ����������, ���� �ݻ��
	m_stMtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���ݻ籤 : ���⼺�� ������, Ư�� �������� ��Ȯ�� �ݻ��
	m_stMtl.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ��ü �߱�
	m_stMtl.Power = 5.0f;
}