#pragma once

class IScene
{
	int m_tag;

public:

	virtual void OnEnter() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnExit() = 0;
	virtual void OnDraw() = 0;

	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {}

	int Tag() { return m_tag; }
	void SetTag(int tag) { m_tag = tag; }
};
 
enum SCENE_TAG
{
	SCENE_NONE, SCENE_LOADING, SCENE_TITLE, SCENE_PLAY, SCENE_SHOP,
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

	int m_nPlayerSkinIndex;

public:
	// ¾À µî·Ï
	void Register(int tag, IScene* pScene);

	// ¾À ¹ÝÈ¯
	IScene* GetScene(int tag);

	// ¾À º¯°æ
	void ChangeScene(int tag);

	// ¾À ¾÷µ¥ÀÌÆ®
	void Update();

	// ¾À µå·Î¿ì
	void Render();

	int Current() { return m_current; }

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetSkinIndex(int index) { m_nPlayerSkinIndex = index; }
	int GetSkinIndex() {return m_nPlayerSkinIndex;	}
};

