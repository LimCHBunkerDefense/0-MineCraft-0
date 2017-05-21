#include "stdafx.h"
#include "cCamera.h"
#include "cInputManager.h"


cCamera::cCamera()
	: m_vEye(0, 5, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_pvTarget(NULL)
	, m_fCameraDistance(5.0f)
	, m_isLButtonDown(false)
	, m_vCamRotAngle(0,0,0)
	, m_cameraIndex(-1)
{
}


cCamera::~cCamera()
{
}

void cCamera::Setup(D3DXVECTOR3* pvTarget)
{
	m_pvTarget = pvTarget; 

	RECT rc; 
	GetClientRect(g_hWnd, &rc); 

	D3DXMATRIXA16 matProj; 
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DX_PI / 4.0F,
		rc.right / (float)rc.bottom,
		1.0f,
		1000.0f); 
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, 5, -m_fCameraDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	if (m_pvTarget)
	{
		m_vLookAt = *m_pvTarget;

		if (m_vEye.y > 0.5f) m_vEye = m_vEye + *m_pvTarget;
		else m_vEye.y = 0.5f;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::Update2(D3DXVECTOR3 dir)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	//D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);

	matR = matRY;

	if (m_pvTarget)
	{
		m_vEye = *m_pvTarget + D3DXVECTOR3(0, 1, 0);
		D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

		m_vLookAt = *m_pvTarget + D3DXVECTOR3(0, 1, 0) + dir * 3;

		//if (m_vEye.y > 0.5f) m_vEye = m_vEye + *m_pvTarget;
		//else m_vEye.y = 0.5f;
	}


	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDOWN:
		if (m_cameraIndex == CAMERA_1) m_isLButtonDown = true;
		break;

	case WM_RBUTTONUP:
		m_isLButtonDown = false;
		break;

	case WM_MOUSEMOVE:
		if (m_isLButtonDown && m_cameraIndex == CAMERA_1)
		{
			POINT deltaMousePos = INPUT->GetMouseDelta();
			m_vCamRotAngle.y += (deltaMousePos.x / 100.f);
			m_vCamRotAngle.x += (deltaMousePos.y / 100.f);
			if (m_vCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
				m_vCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
			if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
				m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;
		}
		else if (m_cameraIndex == CAMERA_2)
		{
			POINT deltaMousePos = INPUT->GetMouseDelta();
			m_vCamRotAngle.x += (deltaMousePos.y / 100.f);
			m_vCamRotAngle.y += (deltaMousePos.x / 100.f);
		}
		break;

	case WM_MOUSEWHEEL:
		if (m_cameraIndex == CAMERA_1)
		{
			m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.f);
			if (m_fCameraDistance < 0.0001f)
				m_fCameraDistance = 0.0001f;
		}
		break;
	}
}

void cCamera::SetPosition()
{
	m_fCameraDistance = m_pvTarget->y * 2.4f;
	m_vLookAt = *m_pvTarget;
	m_vEye = *m_pvTarget + D3DXVECTOR3(0, 0, -m_fCameraDistance);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::SetCamIndex()
{
	m_cameraIndex = m_cameraIndex * -1;

	m_vCamRotAngle = D3DXVECTOR3(0, 0, 0);
	m_fCameraDistance = (5.0f);
	m_vUp = D3DXVECTOR3(0, 1, 0);
}

int cCamera::GetCamIndex()
{
	return m_cameraIndex;
}
