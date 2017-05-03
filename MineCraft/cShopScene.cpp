#include "stdafx.h"
#include "cShopScene.h"
#include "cInputManager.h"
#include "cSurface.h"
#include "cButton.h"
#include "cCubeMan.h"


cShopScene::cShopScene()
	: m_pBg(NULL)
	, m_pGUI_Outline(NULL)
	, m_pGUI_Inform(NULL)
	, m_pSelectButton(NULL)
	, m_pUI_leftButton(NULL)
	, m_pUI_rightButton(NULL)
	, m_pBackButton(NULL)
	, m_pExampleMan01(NULL)
	, m_pExampleMan02(NULL)
	, m_pExampleMan03(NULL)
	, m_pMyMan(NULL)
{
	m_nSkinIndex = SKIN_BATMAN;
}


cShopScene::~cShopScene()
{

}

void cShopScene::OnEnter()
{
	m_pBg = new cSurface();
	m_pBg->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.5F, 0.0F, 0.0F), D3DXVECTOR3(-VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F),
		D3DXVECTOR3(VIEW_WIDTH * 0.5F, VIEW_HEIGHT, 0.0F), D3DXVECTOR3(VIEW_WIDTH * 0.5F, 0.0F, 0.0F), TEXT("Image/TitleScene/bg.png"), false);

	m_pGUI_Outline = new cSurface();
	m_pGUI_Outline->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.1f, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.9f, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.9f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.4f, VIEW_HEIGHT * 0.1f, -0.2f), TEXT("Image/UI/GUI_Outline.png"), false);
	m_pGUI_Outline->SetUI(1.0f, 0.8f);

	m_pGUI_Inform = new cSurface();
	m_pGUI_Inform->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.37f, VIEW_HEIGHT * 0.20f, -0.2f), D3DXVECTOR3(-VIEW_WIDTH * 0.37f, VIEW_HEIGHT * 0.60f, -0.2f),
		D3DXVECTOR3(VIEW_WIDTH * 0.06f, VIEW_HEIGHT * 0.60f, -0.2f), D3DXVECTOR3(VIEW_WIDTH * 0.06f, VIEW_HEIGHT * 0.20f, -0.2f), TEXT("Image/UI/GUI_Inform.png"), false);
	m_pGUI_Inform->SetUI(1.0f, 0.8f);

	m_pUI_leftButton = new cButton();
	m_pUI_leftButton->Setup(D3DXVECTOR3(-VIEW_WIDTH * 0.37f, VIEW_HEIGHT * 0.67f, -0.3f), D3DXVECTOR3(-VIEW_WIDTH * 0.37f, VIEW_HEIGHT * 0.82f, -0.3f),
		D3DXVECTOR3(-VIEW_WIDTH * 0.33f, VIEW_HEIGHT * 0.82f, -0.3f), D3DXVECTOR3(-VIEW_WIDTH * 0.33f, VIEW_HEIGHT * 0.67f, -0.3f), D3DCOLOR_XRGB(175, 175, 175, 0.8f));

	m_pUI_rightButton = new cButton();
	m_pUI_rightButton->Setup(D3DXVECTOR3(VIEW_WIDTH * 0.0f, VIEW_HEIGHT * 0.67f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.0f, VIEW_HEIGHT * 0.82f, -0.3f),
		D3DXVECTOR3(VIEW_WIDTH * 0.04f, VIEW_HEIGHT * 0.82f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.04f, VIEW_HEIGHT * 0.67f, -0.3f), D3DCOLOR_XRGB(175, 175, 175, 0.8f));

	m_pSelectButton = new cButton();
	m_pSelectButton->Setup(D3DXVECTOR3(VIEW_WIDTH * 0.17f, VIEW_HEIGHT * 0.29f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.17f, VIEW_HEIGHT * 0.35f, -0.3f),
		D3DXVECTOR3(VIEW_WIDTH * 0.33f, VIEW_HEIGHT * 0.35f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.33f, VIEW_HEIGHT * 0.29f, -0.3f), D3DCOLOR_XRGB(175, 175, 175, 0.8f));
	//m_pSelectButton->SetText(("Select"), 40, D3DCOLOR_XRGB(0, 0, 0, 0));

	m_pBackButton = new cButton();
	m_pBackButton->Setup(D3DXVECTOR3(VIEW_WIDTH * 0.10f, VIEW_HEIGHT * 0.29f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.10f, VIEW_HEIGHT * 0.35f, -0.3f),
		D3DXVECTOR3(VIEW_WIDTH * 0.16f, VIEW_HEIGHT * 0.35f, -0.3f), D3DXVECTOR3(VIEW_WIDTH * 0.16f, VIEW_HEIGHT * 0.29f, -0.3f), D3DCOLOR_XRGB(175, 175, 175, 0.8f));

	SetupExampleMan();
	
	m_pMyMan = new cCubeMan;
	m_pMyMan->SetScale(180.0f);
	m_pMyMan->Setup();
	m_pMyMan->SetRotY(D3DX_PI);
	m_pMyMan->SetPosition(VIEW_WIDTH * 0.22f, VIEW_HEIGHT * 0.40f, -0.3f);
	m_pMyMan->SetTag(CHARACTER_MY);

	Set_Light();
}

void cShopScene::OnUpdate()
{
	if (INPUT->IsKeyDown(VK_BACK)) SCENE->ChangeScene(SCENE_TITLE);
	if (m_pUI_leftButton)	m_pUI_leftButton->Update();
	if (m_pUI_rightButton)	m_pUI_rightButton->Update();
	if (m_pSelectButton)	m_pSelectButton->Update();
	if (m_pBackButton)		m_pBackButton->Update();
	if (m_pExampleMan01) m_pExampleMan01->Update();
	if (m_pExampleMan02) m_pExampleMan02->Update();
	if (m_pExampleMan03) m_pExampleMan03->Update();
	if (m_pMyMan) m_pMyMan->Update();

	UpdateExampleMan();					// ���� �ɸ��� ���� Ŀ���� ����, ���� �ɸ��Ͱ� Y������ ȸ���ϵ���.
	UpdateExampleSkin();				// ���� �ɸ��� ��Ų ����ǵ���
	SelectSkin();						// �÷��̾ ��Ų ����ǵ���
}

void cShopScene::OnDraw()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	m_pBg->Render();
	m_pGUI_Outline->Render();
	m_pGUI_Inform->Render();

	m_pUI_leftButton->Render();
	m_pUI_rightButton->Render();
	
	m_pSelectButton->Render();
	m_pBackButton->Render();

	m_pExampleMan01->Render();
	m_pExampleMan02->Render();
	m_pExampleMan03->Render();
	m_pMyMan->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cShopScene::OnExit()
{
	SAFE_DELETE(m_pUI_rightButton);
	SAFE_DELETE(m_pUI_leftButton);
	SAFE_DELETE(m_pSelectButton);
	SAFE_DELETE(m_pGUI_Inform);
	SAFE_DELETE(m_pGUI_Outline);
	SAFE_DELETE(m_pBg);
	SAFE_DELETE(m_pExampleMan01);
	SAFE_DELETE(m_pExampleMan02);
	SAFE_DELETE(m_pExampleMan03);
	SAFE_DELETE(m_pMyMan);
}

void cShopScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cShopScene::Set_Light()
{
	D3DLIGHT9 stLight;
	{
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		stLight.Type = D3DLIGHT_DIRECTIONAL;
		stLight.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		stLight.Specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		D3DXVECTOR3 vDir(0.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		g_pD3DDevice->SetLight(0, &stLight);
	}

	g_pD3DDevice->LightEnable(0, true);
}

void cShopScene::SetupExampleMan()
{
	m_pExampleMan01 = new cCubeMan;
	m_pExampleMan01->SetScale(65.0f);
	m_pExampleMan01->Setup();
	m_pExampleMan01->SetRotY(D3DX_PI);
	m_pExampleMan01->SetPosition(VIEW_WIDTH * -0.24f, VIEW_HEIGHT * 0.65f, -70.0f);
	m_pExampleMan01->SetTag(CHARACTER_EXAMPLE);

	m_pExampleMan02 = new cCubeMan;
	m_pExampleMan02->SetScale(65.0f);
	m_pExampleMan02->Setup();
	m_pExampleMan02->SetRotY(D3DX_PI);
	m_pExampleMan02->SetPosition(VIEW_WIDTH * -0.145f, VIEW_HEIGHT * 0.65f, -70.0f);
	m_pExampleMan02->SetTag(CHARACTER_EXAMPLE);

	m_pExampleMan03 = new cCubeMan;
	m_pExampleMan03->SetScale(65.0f);
	m_pExampleMan03->Setup();
	m_pExampleMan03->SetRotY(D3DX_PI);
	m_pExampleMan03->SetPosition(VIEW_WIDTH * -0.05f, VIEW_HEIGHT * 0.65f, -70.0f);
	m_pExampleMan03->SetTag(CHARACTER_EXAMPLE);
}

void cShopScene::UpdateExampleMan()
{
	if (INPUT->IsCollided(D3DXVECTOR2(330, 150), D3DXVECTOR2(420, 330)))
	{
		m_pExampleMan01->SetRotY(m_pExampleMan01->GetRotY() + D3DX_PI * 0.02);
	}
	else
	{
		m_pExampleMan01->SetRotY(D3DX_PI - 0.30f);
	}

	if (INPUT->IsCollided(D3DXVECTOR2(330, 150), D3DXVECTOR2(420, 330)))
	{
		m_pExampleMan02->SetRotY(m_pExampleMan02->GetRotY() + D3DX_PI * 0.02);
	}
	else
	{
		m_pExampleMan02->SetRotY(D3DX_PI - 0.20f);
	}

	if (INPUT->IsCollided(D3DXVECTOR2(330, 150), D3DXVECTOR2(420, 330)))
	{
		m_pExampleMan03->SetRotY(m_pExampleMan03->GetRotY() + D3DX_PI * 0.02);
	}
	else
	{
		m_pExampleMan03->SetRotY(D3DX_PI);
	}
}


void cShopScene::UpdateExampleSkin()
{

	if (m_pUI_leftButton->IsClicked())
	{
		m_nSkinIndex--;
		if (m_nSkinIndex < 1) m_nSkinIndex = SKIN_BATMAN;
	}

	if (m_pUI_rightButton->IsClicked())
	{
		m_nSkinIndex++;
		if (m_nSkinIndex > 4) m_nSkinIndex = SKIN_SPIDER;
	}

	switch (m_nSkinIndex)
	{
	case SKIN_BATMAN:
		m_pExampleMan01->SetTexture(g_pTextureManager->GetTexture("batman"));
		if (INPUT->IsCollided(D3DXVECTOR2(330, 150), D3DXVECTOR2(420, 330)) && INPUT->IsMouseDown(MOUSE_LEFT))
			m_pMyMan->SetTexture(g_pTextureManager->GetTexture("batman"));
		break;
	case SKIN_CAPTAIN:
		m_pExampleMan02->SetTexture(g_pTextureManager->GetTexture("CaptainAmerica"));
		if (INPUT->IsCollided(D3DXVECTOR2(330, 150), D3DXVECTOR2(420, 330)) && INPUT->IsMouseDown(MOUSE_LEFT))
			m_pMyMan->SetTexture(g_pTextureManager->GetTexture("CaptainAmerica"));
		break;
	case SKIN_IRON:
		m_pExampleMan03->SetTexture(g_pTextureManager->GetTexture("Ironman"));
		if (INPUT->IsCollided(D3DXVECTOR2(330, 150), D3DXVECTOR2(420, 330)) && INPUT->IsMouseDown(MOUSE_LEFT))
			m_pMyMan->SetTexture(g_pTextureManager->GetTexture("Ironman"));
		break;
	// case SKIN_SPIDER:
	// 	->SetTexture(g_pTextureManager->GetTexture("Spiderman"));
	// 	if (INPUT->IsCollided(D3DXVECTOR2(330, 150), D3DXVECTOR2(420, 330)) && INPUT->IsMouseDown(MOUSE_LEFT))
	// 		m_pMyMan->SetTexture(g_pTextureManager->GetTexture("Spiderman"));
	// 	break;
	}
}

void cShopScene::SelectSkin()
{
	if (m_pSelectButton->IsClicked())
	{
		SCENE->SetSkinIndex(m_nSkinIndex);
	}
}