#include "stdafx.h"
#include "cSceneManager.h"


cSceneManager::cSceneManager()
{
	m_current = 0;
}


cSceneManager::~cSceneManager()
{
}

// �� ���
void cSceneManager::Register(int tag, IScene* pScene)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		m_scenes[tag] = pScene;
		m_scenes[tag]->SetTag(tag);
	}
}

// �� ��ȯ
IScene* cSceneManager::GetScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end()) return NULL;
	return m_scenes[tag]; 
}

// �� ����
void cSceneManager::ChangeScene(int tag)
{
	m_current = tag;
}

// �� ������Ʈ
void cSceneManager::Update()
{
	if (m_currentScene == NULL || m_current != m_currentScene->Tag())
	{
		if (m_currentScene != NULL) m_currentScene->OnExit();
		m_currentScene = GetScene(m_current);
		if (m_currentScene != NULL) m_currentScene->OnEnter();
	}

	if (m_currentScene != NULL) m_currentScene->OnUpdate();
}

// �� ��ο�
void cSceneManager::Render()
{
	if (m_currentScene != NULL) m_currentScene->OnDraw();
}

void cSceneManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_currentScene != NULL)m_currentScene->WndProc(hwnd, message, wParam, lParam);
}