#include "stdafx.h"
#include "cSceneManager.h"


cSceneManager::cSceneManager()
{
	m_current = 0;
}


cSceneManager::~cSceneManager()
{
}

// 씬 등록
void cSceneManager::Register(int tag, IScene* pScene)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		m_scenes[tag] = pScene;
		m_scenes[tag]->SetTag(tag);
	}
}

// 씬 반환
IScene* cSceneManager::GetScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end()) return NULL;
	return m_scenes[tag]; 
}

// 씬 변경
void cSceneManager::ChangeScene(int tag)
{
	m_current = tag;
}

// 씬 업데이트
void cSceneManager::Update()
{
	if (m_currentScene == NULL || m_current != m_currentScene->Tag())
	{
		//if (m_currentScene != NULL) SAFE_RELEASE(m_currentScene); 
		// 현재 각종 Scene은 서용필쌤 수업과 같이 Release를 안만들어서 이 줄을 주석처리함. 
		// 따라서 메모리 할당받은것이 그대로 있을거임... 이거 풀려면 Scene에 전부 Release 처리 해야함.
		m_currentScene = GetScene(m_current);
		if (m_currentScene != NULL) m_currentScene->Setup();
	}

	if (m_currentScene != NULL) m_currentScene->Update();
}

// 씬 드로우
void cSceneManager::Render()
{
	if (m_currentScene != NULL) m_currentScene->Render();
}

void cSceneManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_currentScene != NULL)m_currentScene->WndProc(hwnd, message, wParam, lParam);
}