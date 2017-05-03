#include "stdafx.h"
#include "cSceneManager.h"


cSceneManager::cSceneManager()
{
	m_current = 0;
}


cSceneManager::~cSceneManager()
{
}

// ¾À µî·Ï
void cSceneManager::Register(int tag, IScene* pScene)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		m_scenes[tag] = pScene;
		m_scenes[tag]->SetTag(tag);
	}
}

// ¾À ¹ÝÈ¯
IScene* cSceneManager::GetScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end()) return NULL;
	return m_scenes[tag]; 
}

// ¾À º¯°æ
void cSceneManager::ChangeScene(int tag)
{
	m_current = tag;
}

// ¾À ¾÷µ¥ÀÌÆ®
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

// ¾À µå·Î¿ì
void cSceneManager::Render()
{
	if (m_currentScene != NULL) m_currentScene->OnDraw();
}

void cSceneManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_currentScene != NULL)m_currentScene->WndProc(hwnd, message, wParam, lParam);
}