#pragma once

class IScene
{
	int m_tag;

public:

	virtual void Setup() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}

	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {}

	int Tag() { return m_tag; }
	void SetTag(int tag) { m_tag = tag; }
};

enum SCENE_TAG
{
	SCENE_NONE, SCENE_TITLE, SCENE_PLAY, SCENE_SHOP,
};

#define SCENE cSceneManager::GetInstance()
class cSceneManager
{
public:
	SINGLETONE(cSceneManager);

private:
	map<int, IScene*> m_scenes;
	IScene* m_currentScene;
	int m_current;

public:
	// �� ���
	void Register(int tag, IScene* pScene);

	// �� ��ȯ
	IScene* GetScene(int tag);

	// �� ����
	void ChangeScene(int tag);

	// �� ������Ʈ
	void Update();

	// �� ��ο�
	void Render();

	int Current() { return m_current; }

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

