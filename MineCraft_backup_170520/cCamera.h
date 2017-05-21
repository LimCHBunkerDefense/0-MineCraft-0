#pragma once

enum CAMERA_INDEX
{
	CAMERA_1 = -1, CAMERA_2 = 1
};


class cCamera
{
public:
	cCamera();
	~cCamera();

private : 
	D3DXVECTOR3	 m_vEye; 
	D3DXVECTOR3	 m_vLookAt;
	D3DXVECTOR3	 m_vUp;
	D3DXVECTOR3* m_pvTarget;

	bool		m_isLButtonDown; 
	float		m_fCameraDistance; 
	D3DXVECTOR3 m_vCamRotAngle; 

	int			m_cameraIndex;
public :
	void Setup(D3DXVECTOR3* pvTarget);

	void Update();
	void Update2(D3DXVECTOR3 dir);

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); 

	void SetPosition();
	void SetCamIndex();
	int GetCamIndex();

};

